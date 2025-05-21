#pragma once
#include "../SurfaceResult.h"

class FlatSurface
{
public:
	virtual SurfaceResult GetSurface(double x, double y);
};