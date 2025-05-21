#include "../../../../Header/Scene/Surface/Flat/SolidFlatSurface.h"

SolidFlatSurface::SolidFlatSurface() = default;
SolidFlatSurface::SolidFlatSurface(SurfaceResult surface) {
	Surface = surface;
}

SurfaceResult SolidFlatSurface::GetSurface(double x, double y) {
	return Surface;
}