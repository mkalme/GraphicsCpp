#include "../../../../Header/Scene/Shape/Traced/Plane.h"
#include "../../../../Header/Math/Rotation.h"

Plane::Plane() = default;
Plane::Plane(Vec3f origin, Vec3f normal) {
	Origin = origin;
	Normal = normal;

	m_xRotation = Rotation(atan2(normal.Z, normal.Y));
	double tempZ = normal.Z, tempY = normal.Y;
	m_xRotation.Rotate(tempZ, tempY);
	m_zRotation = Rotation(atan2(normal.X, tempY));
}

double Plane::Intersect(Ray& const ray) {
	return Intersect(Origin, Normal, ray);
}

SurfaceIntersection Plane::SurfaceIntersect(Ray& const ray) {
	double t = Intersect(Origin, Normal, ray);
	if (t < 0) return SurfaceIntersection::NoIntersection();
	
	double x, y;
	TransformPoint(ray.Origin + ray.Direction * t, x, y);

	SurfaceIntersection intersection = SurfaceIntersection(t, Normal);
	intersection.Surface = Surface->GetSurface(x, y);
	
	return intersection;
}

double Plane::Intersect(Vec3f origin, Vec3f normal, Ray& const ray) {
	double denom = normal.Dot(ray.Direction);
	if (fabs(denom) > 0.000001) {
		return (origin - ray.Origin).Dot(normal) / denom;
	}
	return -1;
}

void Plane::TransformPoint(Vec3f point, double &x, double &y)
{
	double xz = point.Z, xy = point.Y;
	m_xRotation.Rotate(xz, xy);

	double zx = point.X;
	m_zRotation.Rotate(zx, xy);

	x = zx;
	y = xz;
}