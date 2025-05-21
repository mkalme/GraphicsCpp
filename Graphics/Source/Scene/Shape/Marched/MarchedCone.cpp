#include "../../../../Header/Scene/Shape/Marched/MarchedCone.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"

double MarchedCone::GetDistance(Ray& const ray) {
	if (ray.Origin.Y < Location.Y && ray.Direction.Y <= 0) return -1;
	if (ray.Origin.Y > Location.Y + Height && ray.Direction.Y >= 0) return -1;

	Vec2f p0 = Vec2f((ray.Origin.GetXZ() - Location.GetXZ()).Length(), ray.Origin.Y - Location.Y);

	if (ray.Origin.Y < Location.Y) {
		if (p0.X * p0.X < Radius * Radius) return fabs(p0.Y);
		return Vec2f(p0.X - Radius, p0.Y).Length();
	}

	Vec2f p1 = Vec2f(Radius, 0), p2 = Vec2f(0, Height);
	double a = fabs((p2.X - p1.X) * (p1.Y - p0.Y) - (p1.X - p0.X) * (p2.Y - p1.Y));
	double b = sqrt((p2.X - p1.X) * (p2.X - p1.X) + (p2.Y - p1.Y) * (p2.Y - p1.Y));

	if (p0.X < Radius) {
		return fmin(fabs(p0.Y), a / b);
	}

	return a / b;
}

void MarchedCone::GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) {
	bool isPlane = (point - Location).DotItself() < Radius * Radius && fabs(point.Y - Location.Y) < 0.00001;

	if (isPlane) {
		normal = Vec3f(0, -1, 0);
		surface = UvSurface->GetSurface(0, 0);
	}
	else {
		double r = sqrt((point.X - Location.X) * (point.X - Location.X) + (point.Z - Location.Z) * (point.Z - Location.Z));
		normal = Vec3f(point.X - Location.X, r * (Radius / Height), point.Z - Location.Z).Normal();

		double u, v;
		GetUv(point, u, v);
		surface = UvSurface->GetSurface(u, v);
	}
}

bool MarchedCone::Contains(Vec3f point) {
	if (point.Y < Location.Y || point.Y > Location.Y + Height) return false;

	double xzSquared = (point - Location).DotItself();
	double radius = (1 - (point.Y - Location.Y) / Height) * Radius;

	return xzSquared < radius * radius;
}

void MarchedCone::GetUv(Vec3f p, double& u, double& v) {
	Vec2f n = p.GetXZ() - Location.GetXZ();

	u = atan2(-n.X, -n.Y) / (2 * Rotation::PI());
	v = ((Location + Vec3f(0, Height, 0)) - p).Length();
}