#include "../../../../Header/Scene/Shape/Traced/Sphere.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"
#include "../../../../Header/Math/Vec3f.h"
#include <Math.h>

Sphere::Sphere() = default;
Sphere::Sphere(Vec3f location, double radius) {
	Location = location;
	Radius = radius;
}

double Sphere::Intersect(Ray& const ray) {
	return Intersect(Location, Radius, ray);
}

SurfaceIntersection Sphere::SurfaceIntersect(Ray& const ray) {
	double t = Intersect(Location, Radius, ray);
	if (t < 0) return SurfaceIntersection::NoIntersection();

	Vec3f normal = ((ray.Origin + ray.Direction * t) - Location) / Radius;

	double u, v;
	GetUv(normal, u, v);

	SurfaceIntersection intersection = SurfaceIntersection(t, normal);
	intersection.Surface = UvSurface->GetSurface(u, v);

	return intersection;
}

void Sphere::GetUv(Vec3f n, double &u, double &v) {
	u = atan2(n.X, -n.Z) / Rotation::PI();
	v = atan2(sqrt(n.X * n.X + n.Z * n.Z), n.Y) / Rotation::PI();
}

bool Sphere::Contains(Vec3f point) {
	return (point - Location).DotItself() < Radius * Radius;
}

double Sphere::Intersect(Vec3f location, double radius, Ray& const ray) {
	Vec3f oc = ray.Origin.Sub(location);

	double b = 2.0 * ray.Direction.Dot(oc);
	double c = oc.DotItself() - radius * radius;

	double t;
	if (!MathUtilities::DetermineRoot(1, b, c, t)) return -1;
	return t;
}