#pragma once
#include "Vec3f.h"

struct Ray
{
public:
	Vec3f Origin;
	Vec3f Direction;

	Ray(Vec3f origin, Vec3f direction);
	Ray();
};

