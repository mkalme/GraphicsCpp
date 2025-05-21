#include "../../../../../Header/Scene/Shape/Marched/Composite/RepeatedMarchedObject.h"
#include "../../../../../Header/Math/MathUtilities.h"

double RepeatedMarchedObject::GetDistance(Ray& const ray) {
	Ray r = Ray(ModPoint(ray.Origin), ray.Direction);
	return Object->GetDistance(r);
}

void RepeatedMarchedObject::GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) {
	return Object->GetNormalAndSurface(ModPoint(point), normal, surface);
}

bool RepeatedMarchedObject::Contains(Vec3f point) {
	return Object->Contains(ModPoint(point));
}

Vec3f RepeatedMarchedObject::ModPoint(Vec3f point) {
	point.X = DoMod(point.X, Corner1.X, Corner2.X - Corner1.X, MaxXCells, MinXCells);
	point.Z = DoMod(point.Z, Corner1.Y, Corner2.Y - Corner1.Y, MaxZCells, MinZCells);
	
	return point;
}

double RepeatedMarchedObject::DoMod(double value, double offset, double width, double maxN, double minN) {
	int n = MathUtilities::DivideNeg(value - offset, width);
	n = fmin(fmax(n, minN), maxN);
	return value - n * width;
}
