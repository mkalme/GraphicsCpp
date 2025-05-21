#pragma once
#include "UvSurface.h";
#include "../../../Math/Vec3f.h";

class SolidUvSurface : public UvSurface
{
public:
	SurfaceResult Surface;

	SolidUvSurface();
	SolidUvSurface(SurfaceResult surface);

	SurfaceResult GetSurface(double u, double v) override;
};

