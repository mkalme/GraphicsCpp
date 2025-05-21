#include "../../../../Header/Scene/Shape/Traced/Cylinder.h"
#include "../../../../Header/Math/Vec2f.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"

Cylinder::Cylinder() = default;
Cylinder::Cylinder(Vec3f location, double radius, UvSurface* surface) {
	Location = location;
	Radius = radius;
	Surface = surface;
}

double Cylinder::Intersect(Ray& const ray) {
    Vec2f o = Vec2f(ray.Origin.Z, ray.Origin.X);
    Vec2f d = Vec2f(ray.Direction.Z, ray.Direction.X);
    Vec2f v = Vec2f(ray.Origin.Z, ray.Origin.X) - Vec2f(Location.Z, Location.X);

    double dLength = d.Length();
    d = d / dLength;

    double a = d.Dot(d);
    double b = 2 * v.Dot(d);
    double c = v.Dot(v) - Radius * Radius;

    double t;
    MathUtilities::DetermineRoot(a, b, c, t);
    
    return t / dLength;
}

SurfaceIntersection Cylinder::SurfaceIntersect(Ray& const ray) {
    Vec2f o = Vec2f(ray.Origin.Z, ray.Origin.X);
    Vec2f d = Vec2f(ray.Direction.Z, ray.Direction.X);
    Vec2f v = Vec2f(ray.Origin.Z, ray.Origin.X) - Vec2f(Location.Z, Location.X);

    double dLength = d.Length();
    d = d / dLength;

    double a = d.Dot(d);
    double b = 2 * v.Dot(d);
    double c = v.Dot(v) - Radius * Radius;

    double t;
    if (!MathUtilities::DetermineRoot(a, b, c, t)) return SurfaceIntersection::NoIntersection();

    Vec2f point = o + d * t;
    t /= dLength;

    Vec3f normal = Vec3f(point.Y - Location.X, 0, point.X - Location.Z) / Radius;
    SurfaceIntersection output(t, normal);

    Vec2f uv = GetUV(normal, ray.Origin.Y + ray.Direction.Y * t, Radius);
    output.Surface = Surface->GetSurface(uv.X, uv.Y);

    return output;
}

Vec2f Cylinder::GetUV(Vec3f n, double y, double r) {
    double u = (atan2(-n.X, -n.Z) / (2 * Rotation::PI()));
    return Vec2f(u, y / (2 * Rotation::PI()));
}

bool Cylinder::Contains(Vec3f point) {
    return (point.GetXZ() - Location.GetXZ()).DotItself() < Radius * Radius;
}