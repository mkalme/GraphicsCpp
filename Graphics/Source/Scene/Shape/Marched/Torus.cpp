#include "../../../../Header/Scene/Shape/Marched/Torus.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"

double Torus::GetDistance(Ray& const ray) {
	if (ray.Origin.Y < Location.Y - Radius2 && ray.Direction.Y <= 0) return -1;
	if (ray.Origin.Y > Location.Y + Radius2 && ray.Direction.Y >= 0) return -1;

	Vec3f point = ray.Origin - Location;

	Vec2f q = Vec2f(point.GetXZ().Length() - Radius1, point.Y);
	return fabs(q.Length() - Radius2);
}

void Torus::GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) {
	Vec3f p2 = Vec3f(point.X, Location.Y, point.Z);
	Vec3f p = SetLengthBetweenVectors(Location, p2, Radius1);
	Vec3f n = point - p;
	
	normal = n / Radius2;

	double u, v;
	GetUv(point, normal, u, v);
	surface = UvSurface->GetSurface(u, v);
}

bool Torus::Contains(Vec3f point) {
	if (point.Y > Location.Y + Radius2 || point.Y < Location.Y - Radius2) return false;

	Vec2f p = Vec2f(point.GetXZ().Length(), point.Y - Location.Y - Radius2);
	return (p - Vec2f(Radius1, 0)).DotItself() <= Radius2 * Radius2 ||
		(p - Vec2f(-Radius1, 0)).DotItself() <= Radius2 * Radius2;
}

Vec3f Torus::SetLengthBetweenVectors(Vec3f o, Vec3f d, double l) {
	double x = d.X - o.X;
	double y = d.Y - o.Y;
	double z = d.Z - o.Z;

	double di = sqrt(x * x + y * y + z * z);
	double lr = l / di;

	return Vec3f(x * lr + o.X, y * lr + o.Y, z * lr + o.Z);
}

void Torus::GetUv(Vec3f p, Vec3f n, double& u, double& v) {
	double hAngle = atan2(p.Z - Location.Z, -p.X + Location.X);
	u = hAngle / Rotation::PI();
	u = (2 - (u + 1)) - 1;

	Rotation rotate = Rotation(hAngle);
	rotate.Rotate(n.X, n.Z);

	v = (atan2(n.X, n.Y) / Rotation::PI() + 1) / 2;
	v = 1 - v;
	v = MathUtilities::NegMod(v - 0.25, 1);
}