#include "../../Header/Renderer/Renderer.h"
#include "../../Header/Utilities/ImageBuffer/ScaledImageBuffer.h"
#include <thread>
#include <vector>
#include <iostream>

Renderer::Renderer(Scene* renderScene, ImageBuffer* imageBuffer, RenderSettings renderSettings) {
    RenderScene = renderScene;
    m_renderImageBuffer = imageBuffer;
    SetSettings(renderSettings);
}

void Renderer::StartAsync() {
    m_isBusyStates.clear();
    m_continueAsync = true;

    for (int i = 0; i < m_renderSettings.ThreadCount; i++) {
        m_isBusyStates.push_back(false);

        int threadCount = m_renderSettings.ThreadCount;
        std::thread thread([this, i, threadCount] { RenderAsync(ThreadInfo(i, threadCount)); });
        thread.detach();
    }
}
void Renderer::StopAsync() {
    m_continueAsync = false;
}

RenderSettings Renderer::GetSettings() {
    return m_renderSettings;
}
void Renderer::SetSettings(RenderSettings settings) {
    m_renderSettings = settings;
    SetRenderImageBuffer(m_renderImageBuffer);
}

ImageBuffer* Renderer::GetRenderImageBuffer() {
    return m_renderImageBuffer;
}
void Renderer::SetRenderImageBuffer(ImageBuffer* imageBuffer) {
    m_renderImageBuffer = imageBuffer;
    m_scaledImageBuffer = new ScaledImageBuffer(imageBuffer, m_renderSettings.Scale);
}

void Renderer::Render() {
    RenderScene->CameraObj->SetDimensions(m_scaledImageBuffer->GetWidth(), m_scaledImageBuffer->GetHeight());

    for (int i = 0; i < m_isBusyStates.size(); i++) {
        m_isBusyStates[i] = true;
    }

    while (AreThreadsBusy()) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(0));
    }
}

bool Renderer::AreThreadsBusy() {
    for (int i = 0; i < m_isBusyStates.size(); i++) {
        if (m_isBusyStates[i]) return true;
    }

    return false;
}

void Renderer::RenderAsync(ThreadInfo info) {
    while (m_continueAsync) {
        if (!m_isBusyStates[info.Index]) continue;

        int width = m_scaledImageBuffer->GetWidth(), height = m_scaledImageBuffer->GetHeight();

        int delta = (int)ceilf(width / (double)info.ThreadCount);
        int y1 = delta * info.Index;
        int y2 = std::min(y1 + delta, height);

        Ray* rays = RenderScene->CameraObj->GenerateRays(info);
        for (int y = y1; y < y2; y++) {
            for (int x = 0; x < width; x++) {
                Ray ray = rays[width * y + x];
                Vec3f color = TraceRay(ray, 1, 1).Clamp(0, 1);

                if (m_renderSettings.Vignette.Enabled) {
                    Vec2f c = Vec2f(width / 2, height / 2);
                    Vec2f p = Vec2f(x, y);

                    double d = (p - c).DotItself();
                    if (d > pow(width / 2 * m_renderSettings.Vignette.Radius, 2)) {
                        d = sqrt(d);
                        d -= width / 2 * m_renderSettings.Vignette.Radius;

                        const double NORMALIZATION_CONSTANT = 1000.0;

                        double strength = d * m_renderSettings.Vignette.Strength * (NORMALIZATION_CONSTANT / width);
                        color = color * (1 - strength) + (m_renderSettings.Vignette.Color * strength);
                        color = color.Clamp(0, 1);
                    }
                }

                m_scaledImageBuffer->SetPixel(x, y, color);
            }
        }

        m_isBusyStates[info.Index] = false;
    }
}

Vec3f Renderer::TraceRay(Ray ray, int refractionDepth, int depth) {
    SurfaceIntersection intersect = DoSurfaceIntersect(ray);
    if (!intersect.DoesIntersect()) return RenderScene->Sky->GetColor(ray.Direction);

    Vec3f point = ray.Origin + ray.Direction * (intersect.T * 0.999999);
    Vec3f color = intersect.Surface.Color;
    Vec3f specular = Vec3f(0);
    Vec3f shade = GetShade(intersect.Normal, point, ray.Direction, intersect.Surface.SpecularPow, specular);
    color = color * shade;

    if (depth < m_renderSettings.MaxDepth && (intersect.Surface.ReflectionIndex > 0 || intersect.Surface.FresnelIndex > 0)) {
        Ray reflectedRay = Ray(point, ReflectRay(ray.Direction, intersect.Normal));
        Vec3f reflectedColor = TraceRay(reflectedRay, refractionDepth + 1, depth + 1);
        double angle = 1 - fabs(reflectedRay.Direction.Dot(intersect.Normal));
        double reflection = intersect.Surface.ReflectionIndex + (1 - intersect.Surface.ReflectionIndex) * intersect.Surface.FresnelIndex * angle;
        reflection = fmin(reflection, 1);
        color = color * (1 - reflection) + reflectedColor * reflection;
    }

    if (refractionDepth < m_renderSettings.MaxRefractionDepth && intersect.Surface.RefractionIndex > 0) {
        Vec3f refract = Refract(ray.Direction, intersect.Normal, intersect.Surface.RefractionIndex);
        if (refract != 0) {
            Vec3f rColor = TraceRay(Ray(ray.Origin + ray.Direction * (intersect.T * 1.000001), refract), refractionDepth + 1, depth + 1);

            color = color * (1 - intersect.Surface.RefractionReflectionIndex) + rColor * intersect.Surface.RefractionReflectionIndex;
        }
    }

    color = (color + specular).Clamp(0, 1);

    Vec3f fogColor; double fogIntensity;
    RenderScene->Fog->GetColorAndIntensity(intersect.T, fogColor, fogIntensity);
    if (fogIntensity > 0) {
        color = color * (1 - fogIntensity) + fogColor * fogIntensity;
    }

    return color;
}

Vec3f Renderer::ReflectRay(Vec3f d, Vec3f n) {
    return d - (n * d.Dot(n)) * 2;
}

Vec3f Renderer::Refract(Vec3f I, Vec3f N, double ior) {
    double cosi = I.Dot(N);
    cosi = fmax(-1, cosi);
    cosi = fmin(1, cosi);

    double etai = 1, etat = ior;

    Vec3f n = N;
    if (cosi < 0) {
        cosi = -cosi;
    }
    else {
        double temp = etai;
        etai = etat;
        etat = temp;

        n = N.Inverse();
    }

    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi);

    return k < 0 ? 0 : I * eta + n * (eta * cosi - sqrt(k));
}

SurfaceIntersection Renderer::DoSurfaceIntersect(Ray ray) {
    SurfaceIntersection output = SurfaceIntersection::NoIntersection();

    for (int i = 0; i < RenderScene->Objects.size(); i++){
        Object* obj = RenderScene->Objects[i];

        SurfaceIntersection intersection = obj->SurfaceIntersect(ray);
        if (output.DoesIntersect() && (!intersection.DoesIntersect() || intersection.T > output.T)) continue;

        output = intersection;
    }

    return output;
}

Vec3f Renderer::GetShade(Vec3f normal, Vec3f point, Vec3f rayD, double ks, Vec3f &specular) {
    Vec3f diffuse = 0;

    for (int i = 0; i < RenderScene->LightSources.size(); i++) {
        Light* light = RenderScene->LightSources[i];
        
        Vec3f dir;
        double distance;
        light->GetDirectionAndDistance(point, dir, distance);
        if (Hit(Ray(point, dir), distance)) continue;

        const double MAX_LUMENS = 1000;
        double angle = fabs(dir.Dot(normal));
        double lumens = light->GetLumens(distance) * angle;;
        lumens = lumens > MAX_LUMENS ? MAX_LUMENS : lumens;
        diffuse = diffuse + light->Color * (lumens / MAX_LUMENS);

        Vec3f r = ReflectRay(dir, normal);
        specular = specular + (light->Color * ks * pow(fmax(0, r.Dot(rayD)), 100.0));
    }

    return (RenderScene->AmbientLight + diffuse).Clamp(0, 1);
}

bool Renderer::Hit(Ray ray, double distance) {
    for (int i = 0; i < RenderScene->Objects.size(); i++) {
        Object* obj = RenderScene->Objects[i];

        double intersection = obj->Intersect(ray);
        if (intersection > 0 && intersection < distance) return true;
    }

    return false;
}