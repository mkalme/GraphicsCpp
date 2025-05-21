#pragma once
#include "../SurfaceResult.h"
#include "FlatSurface.h"

class LineFlatSurface : public FlatSurface
{
public:
	SurfaceResult FirstSurfaceResult;
	SurfaceResult SecondSurfaceResult;

	double FirstLineWidth;
	double SecondLineWidth;

	double Offset;

	SurfaceResult GetSurface(double x, double y) override;
};