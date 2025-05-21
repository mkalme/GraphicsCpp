#pragma once
#include "../../Math/Vec3f.h"

struct SurfaceResult
{
	Vec3f Color;
	double ReflectionIndex;
	double FresnelIndex;
	double SpecularPow;
	double RefractionIndex;
	double RefractionReflectionIndex;

	SurfaceResult();
	SurfaceResult(Vec3f color, double reflectionIndex, double fresnelIndex, double specularPow);
};