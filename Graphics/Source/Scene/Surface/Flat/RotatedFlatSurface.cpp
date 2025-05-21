#include "../../../../Header/Scene/Surface/Flat/RotatedFlatSurface.h"

RotatedFlatSurface::RotatedFlatSurface(FlatSurface* wrapped) {
	Wrapped = wrapped;
}
RotatedFlatSurface::RotatedFlatSurface(FlatSurface* wrapped, Rotation rotation) {
	Wrapped = wrapped;
	RotatedBy = rotation;
}

SurfaceResult RotatedFlatSurface::GetSurface(double x, double y) {
	RotatedBy.Rotate(x, y);
	return Wrapped->GetSurface(x, y);
}