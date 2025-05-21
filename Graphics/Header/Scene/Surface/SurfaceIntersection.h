#pragma once
#include "SurfaceResult.h"

struct SurfaceIntersection
{
public:
	double T;
	Vec3f Normal;
	SurfaceResult Surface;

	SurfaceIntersection(double intersect, Vec3f normal);
	SurfaceIntersection();

	bool DoesIntersect();
	static SurfaceIntersection NoIntersection();
};

