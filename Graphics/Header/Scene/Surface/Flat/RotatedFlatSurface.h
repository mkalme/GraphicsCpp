#pragma once
#include "../SurfaceResult.h"
#include "../../../Math/Rotation.h"
#include "FlatSurface.h"

class RotatedFlatSurface : public FlatSurface
{
public:
	Rotation RotatedBy = Rotation::FromDegrees(0);
	FlatSurface* Wrapped;

	RotatedFlatSurface(FlatSurface* wrapped);
	RotatedFlatSurface(FlatSurface* wrapped, Rotation rotation);

	SurfaceResult GetSurface(double x, double y) override;
};