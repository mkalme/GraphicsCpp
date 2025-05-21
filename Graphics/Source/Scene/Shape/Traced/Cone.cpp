#include "../../../../Header/Scene/Shape/Traced/Cone.h"
#include "../../../../Header/Math/MathUtilities.h"
#include "../../../../Header/Scene/Shape/Traced/Plane.h"

double Cone::Intersect(Ray& const ray) {
	double t;
	IntersectWithPlane(ray, t);

	return t;
}

SurfaceIntersection Cone::SurfaceIntersect(Ray& const ray) {
	double t;
	bool isPlane = IntersectWithPlane(ray, t);

	if (t < 0) return SurfaceIntersection::NoIntersection();

	if (isPlane) {
		SurfaceIntersection output = SurfaceIntersection(t, Vec3f(0, -1, 0));
		output.Surface = UvSurface->GetSurface(0, 0);
		return output;
	} else {
		Vec3f p = ray.Origin + ray.Direction * t;

		double r = sqrt((p.X - Location.X) * (p.X - Location.X) + (p.Z - Location.Z) * (p.Z - Location.Z));
		Vec3f n = Vec3f(p.X - Location.X, r * (Radius / Height), p.Z - Location.Z);
		n = n.Normal();

		double u, v;
		GetUv(p, u, v);

		SurfaceIntersection output = SurfaceIntersection(t, n);
		output.Surface = UvSurface->GetSurface(u, v);

		return output;
	}
}

bool Cone::IntersectWithPlane(Ray& const ray, double& t) {
	double A = ray.Origin.X - Location.X;
	double B = ray.Origin.Z - Location.Z;
	double D = Height - ray.Origin.Y + Location.Y;

	double tan = (Radius / Height) * (Radius / Height);

	double a = (ray.Direction.X * ray.Direction.X) + (ray.Direction.Z * ray.Direction.Z) - (tan * (ray.Direction.Y * ray.Direction.Y));
	double b = (2 * A * ray.Direction.X) + (2 * B * ray.Direction.Z) + (2 * tan * D * ray.Direction.Y);
	double c = (A * A) + (B * B) - (tan * (D * D));

	double planeT = Plane::Intersect(Location, Vec3f(0, -1, 0), ray);
	double xzSquared = ((ray.Origin + ray.Direction * planeT) - Location).DotItself();
	if (xzSquared > Radius * Radius) planeT = -1;

	double coneT_0, coneT_1, coneT_max;
	if (!MathUtilities::DetermineRoot(a, b, c, coneT_0, coneT_1)) {
		t = planeT;
		return t >= 0;
	}

	double y;
	if (!ValidateY(ray, coneT_0, coneT_1, coneT_max, y)) {
		t = planeT;
		return t >= 0;
	}

	if (y < Location.Y) coneT_max = -1;

	if (planeT >= 0 && (coneT_max > planeT || coneT_max < 0)) {
		t = planeT;
		return true;
	}

	t = coneT_max;
	return false;
}

bool Cone::ValidateY(Ray& const ray, double coneT_0, double coneT_1, double &coneT_max, double &y) {
	if (coneT_0 > coneT_1) {
		double temp = coneT_0;
		coneT_0 = coneT_1;
		coneT_1 = temp;
	}

	coneT_max = coneT_0;
	bool firstIsNeg = false;
	if (coneT_max < 0) {
		coneT_max = coneT_1;
		firstIsNeg = true;
	}

	y = ray.Origin.Y + ray.Direction.Y * coneT_max;
	if (y < Location.Y + Height) return true;

	if (firstIsNeg) return false;

	coneT_max = coneT_1;

	y = ray.Origin.Y + ray.Direction.Y * coneT_max;
	return y < Location.Y + Height;
}

bool Cone::Contains(Vec3f point) {
	if (point.Y < Location.Y || point.Y > Location.Y + Height) return false;

	double xzSquared = (point - Location).DotItself();
	double radius = (1 - (point.Y - Location.Y) / Height) * Radius;

	return xzSquared < radius * radius;
}

void Cone::GetUv(Vec3f p, double& u, double& v) {
	Vec2f n = p.GetXZ() - Location.GetXZ();

	u = atan2(-n.X, -n.Y) / (2 * Rotation::PI());
	v = ((Location + Vec3f(0, Height, 0)) - p).Length();
}