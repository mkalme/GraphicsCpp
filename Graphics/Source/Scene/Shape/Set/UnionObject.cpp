#include "../../../../Header/Scene/Shape/Set/UnionObject.h"

UnionObject::UnionObject(std::vector<Object*> objects) {
	Objects = objects;
}

double UnionObject::Intersect(Ray& const ray) {
	double t = -1;

	for (int i = 0; i < Objects.size(); i++) {
		double tt = Objects[i]->Intersect(ray);
		if (tt < 0) continue;
		if (t < 0 || tt < t) t = tt;
	}

	return t;
}

SurfaceIntersection UnionObject::SurfaceIntersect(Ray& const ray) {
	SurfaceIntersection output = SurfaceIntersection::NoIntersection();

	for (int i = 0; i < Objects.size(); i++) {
		Object* obj = Objects[i];

		SurfaceIntersection intersection = obj->SurfaceIntersect(ray);
		if (output.DoesIntersect() && (!intersection.DoesIntersect() || intersection.T > output.T)) continue;

		output = intersection;
	}

	return output;
}

bool UnionObject::Contains(Vec3f point) {
	for (int i = 0; i < Objects.size(); i++) {
		if (!Objects[i]->Contains(point)) return false;
	}

	return true;
}