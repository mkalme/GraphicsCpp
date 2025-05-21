#include "../../../Header/Scene/Shape/Object.h"

double Object::Intersect(Ray& const ray) {
	return -1;
}

SurfaceIntersection Object::SurfaceIntersect(Ray& const ray) {
	return SurfaceIntersection::NoIntersection();
}

bool Object::Contains(Vec3f point) {
	return false;
}