#include "../../../../Header/Scene/Shape/Marched/MarchedObject.h"

double MarchedObject::Intersect(Ray& const ray) {
	Vec3f o = ray.Origin;
	double t = 0;

	int step = 0;
	while (step++ < MaxSteps) {
		Ray r = Ray(o, ray.Direction);
		double tt = GetDistance(r);

		if (tt < 0) return -1;
		if (tt < 0.000000001) return fmax((t + tt) - 0.0000001, 0.0000001);

		t += tt;
		o = ray.Origin + ray.Direction * t;
	}

	return -1;
}

SurfaceIntersection MarchedObject::SurfaceIntersect(Ray& const ray) {
	double t = Intersect(ray);
	Vec3f point = ray.Origin + ray.Direction * t;

	Vec3f normal;
	SurfaceResult surface;
	GetNormalAndSurface(point, normal, surface);

	SurfaceIntersection output(t, normal);
	output.Surface = surface;

	return output;
}

bool MarchedObject::Contains(Vec3f point) {
	return false;
}

double MarchedObject::GetDistance(Ray& const ray) {
	return -1;
}

void MarchedObject::GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) {
	normal = Vec3f::Empty();
	surface = SurfaceResult();
}
