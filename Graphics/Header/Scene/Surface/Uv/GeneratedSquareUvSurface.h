#pragma once
#include "UvSurface.h";

class GeneratedSquareUvSurface : public UvSurface
{
public:
	Vec3f FirstColor;
	Vec3f SecondColor;
	SurfaceResult DefaultSurface;

	double SquareSize_U = 0.02;
	double SquareSize_V = 0.02;

	GeneratedSquareUvSurface();
	GeneratedSquareUvSurface(Vec3f firstColor, Vec3f secondColor, SurfaceResult defaultSurface);

	SurfaceResult GetSurface(double u, double v) override;
};

