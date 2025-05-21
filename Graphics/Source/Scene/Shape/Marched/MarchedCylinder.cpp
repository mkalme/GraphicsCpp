#include "../../../../Header/Scene/Shape/Marched/MarchedCylinder.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"

double MarchedCylinder::GetDistance(Ray& const ray) {
	return fabs((ray.Origin.GetXZ() - Location.GetXZ()).Length() - Radius);
}

void MarchedCylinder::GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) {
	normal = (point - Vec3f(Location.X, point.Y, Location.Z)) / Radius;

	Vec2f uv = GetUv(normal, point.Y, Radius);
	surface = UvSurface->GetSurface(uv.X, uv.Y);
}

bool MarchedCylinder::Contains(Vec3f point) {
	return(point.GetXZ() - Location.GetXZ()).DotItself() < Radius * Radius;
}

Vec2f MarchedCylinder::GetUv(Vec3f n, double y, double r) {
	double u = (atan2(-n.X, -n.Z) / (2 * Rotation::PI()));
	return Vec2f(u, y / (2 * Rotation::PI()));
}