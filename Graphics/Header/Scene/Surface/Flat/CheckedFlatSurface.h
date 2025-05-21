#pragma once
#include "../SurfaceResult.h"
#include "FlatSurface.h"

class CheckedFlatSurface : public FlatSurface
{
public:
	double Zoom;
	SurfaceResult FirstSurfaceResult;
	SurfaceResult SecondSurfaceResult;

	CheckedFlatSurface();
	CheckedFlatSurface(double zoom);

	SurfaceResult GetSurface(double x, double y) override;
};

