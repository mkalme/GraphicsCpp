#pragma once
#include "../SurfaceResult.h"
#include "FlatSurface.h"

class SolidFlatSurface : public FlatSurface
{
public:
	SurfaceResult Surface = SurfaceResult();

	SolidFlatSurface();
	SolidFlatSurface(SurfaceResult surface);

	SurfaceResult GetSurface(double x, double y) override;
};

