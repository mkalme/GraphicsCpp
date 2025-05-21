#include "../../../../Header/Scene/Surface/Flat/CheckedFlatSurface.h"

CheckedFlatSurface::CheckedFlatSurface() = default;
CheckedFlatSurface::CheckedFlatSurface(double zoom) {
	Zoom = zoom;
	FirstSurfaceResult = SurfaceResult();
	SecondSurfaceResult = SurfaceResult();
}

SurfaceResult CheckedFlatSurface::GetSurface(double x, double y) {
	return ((int)floor(x * Zoom) % 2 == 0) ^ ((int)floor(y * Zoom) % 2 == 0) ? FirstSurfaceResult : SecondSurfaceResult;
}