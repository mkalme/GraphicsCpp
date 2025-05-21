#include "../../../../Header/Scene/Shape/Marched/MarchedSphere.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"

double MarchedSphere::GetDistance(Ray& const ray) {
	if (ray.Origin.Y < Location.Y - Radius && ray.Direction.Y <= 0) return -1;
	if (ray.Origin.Y > Location.Y + Radius && ray.Direction.Y >= 0) return -1;

	return fabs((ray.Origin - Location).Length() - Radius);
}

void MarchedSphere::GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) {
	normal = (point - Location) / Radius;

	double u, v;
	GetUv(point, normal, u, v);
	surface = UvSurface->GetSurface(u, v);
}

bool MarchedSphere::Contains(Vec3f point) {
	return(point - Location).DotItself() < Radius* Radius;
}

void MarchedSphere::GetUv(Vec3f p, Vec3f n, double& u, double& v) {
	u = atan2(n.X, -n.Z) / Rotation::PI();
	v = atan2(sqrt(n.X * n.X + n.Z * n.Z), n.Y) / Rotation::PI();
}