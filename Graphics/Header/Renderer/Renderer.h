#pragma once
#include "../Scene/Scene.h"
#include "../../Header/Utilities/ImageBuffer/ScaledImageBuffer.h"
#include "ThreadInfo.h"
#include "RenderSettings.h"

class Renderer
{
public:
	Scene* RenderScene;

	Renderer(Scene* renderScene, ImageBuffer* imageBuffer, RenderSettings renderSettings);

	void Render();

	void StartAsync();
	void StopAsync();

	RenderSettings GetSettings();
	void SetSettings(RenderSettings settings);

	ImageBuffer* GetRenderImageBuffer();
	void SetRenderImageBuffer(ImageBuffer* renderImageBuffer);
private:
	RenderSettings m_renderSettings;
	ImageBuffer* m_renderImageBuffer = 0;
	ScaledImageBuffer* m_scaledImageBuffer = 0;
	bool m_continueAsync = true;
	std::vector<bool> m_isBusyStates;

	bool AreThreadsBusy();
	void RenderAsync(ThreadInfo info);

	Vec3f TraceRay(Ray ray, int refractionDepth, int depth);
	Vec3f ReflectRay(Vec3f d, Vec3f n);
	Vec3f Refract(Vec3f I, Vec3f N, double ior);

	SurfaceIntersection DoSurfaceIntersect(Ray ray);
	Vec3f GetShade(Vec3f normal, Vec3f point, Vec3f rayD, double ks, Vec3f& specular);
	bool Hit(Ray ray, double distance);
};

