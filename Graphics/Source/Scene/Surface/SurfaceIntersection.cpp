#include "../../../Header/Scene/Surface/SurfaceIntersection.h"

SurfaceIntersection::SurfaceIntersection(double intersect, Vec3f normal) {
	T = intersect;
	Normal = normal;
}
SurfaceIntersection::SurfaceIntersection() = default;

bool SurfaceIntersection::DoesIntersect() {
	return T >= 0;
}
SurfaceIntersection SurfaceIntersection::NoIntersection() {
	return SurfaceIntersection(-1, Vec3f::Empty());
}