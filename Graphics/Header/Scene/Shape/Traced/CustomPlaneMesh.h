#pragma once
#include "../Object.h"
#include "../../../Scene/Surface/SurfaceResult.h"
#include "../../../Math/Rotation.h"
#include <functional>

struct CustomPlaneIntersection
{
    double T;
    Vec2f Coords;
    Vec3f Normal;

    CustomPlaneIntersection(double t, Vec2f coords, Vec3f normal) {
        T = t;
        Coords = coords;
        Normal = normal;
    }

    static CustomPlaneIntersection NoIntersection() {
        return CustomPlaneIntersection(-1, Vec2f::Empty(), Vec3f::Empty());
    }
};

class CustomPlane
{
public:
    Vec3f Vertex0;
    Rotation Vertical;
    Rotation Horizontal;
    Vec3f Normal;

    std::function<bool(Vec2f)> Validator;

    CustomPlane() = default;
    CustomPlane(Vec3f vertex0, Rotation vertical, Rotation horizontal, Vec3f normal, std::function<bool(Vec2f)> validator) {
        Vertex0 = vertex0;
        Vertical = vertical;
        Horizontal = horizontal;
        Normal = normal;
        Validator = validator;

        m_origin = Vec2f(0);
        TransformPoint(Vertex0, m_origin.X, m_origin.Y);
    }

    CustomPlaneIntersection Intersect(Ray& const ray) {
        double t;

        double denom = Normal.Dot(ray.Direction);
        if (abs(denom) > 0.000001) {
            t = (Vertex0 - ray.Origin).Dot(Normal) / denom;
        }
        else {
            return CustomPlaneIntersection::NoIntersection();
        }

        if (t < 0) return CustomPlaneIntersection::NoIntersection();

        double x, y;
        TransformPoint(ray.Origin + ray.Direction * t, x, y);
        if (!Validator(Vec2f(x, y))) return CustomPlaneIntersection::NoIntersection();

        return CustomPlaneIntersection(t, Vec2f(x, y), Normal);
    }
private:
    Vec2f m_origin;

    void TransformPoint(Vec3f point, double& x, double& y) {
        double xh = point.X, zh = point.Z;
        Horizontal.Rotate(xh, zh);

        double yV = point.Y;
        Vertical.Rotate(zh, yV);

        x = -xh - m_origin.X;
        y = zh - m_origin.Y;
    }
};

class CustomPlaneMesh : public Object
{
public:
    CustomPlane* Planes = 0;
    int Count = 0;
    bool UseCustomNormals;

    SurfaceResult Surface = SurfaceResult();

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
};