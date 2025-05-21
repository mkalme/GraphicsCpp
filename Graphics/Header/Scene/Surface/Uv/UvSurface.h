#pragma once
#include "../../../Math/Vec3f.h"
#include "../SurfaceResult.h"

class UvSurface
{
public:
	virtual SurfaceResult GetSurface(double u, double v);
};

