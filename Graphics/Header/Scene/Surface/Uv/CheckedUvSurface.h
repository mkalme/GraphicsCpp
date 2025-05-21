#pragma once
#include "UvSurface.h";

class CheckedUvSurface : public UvSurface
{
public:
	SurfaceResult FirstCell;
	SurfaceResult SecondCell;

	double SquareSize_U = 0.02;
	double SquareSize_V = 0.02;

	SurfaceResult GetSurface(double u, double v) override;
};