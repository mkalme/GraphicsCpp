#include "../../../../Header/Scene/Surface/Uv/SolidUvSurface.h"

SolidUvSurface::SolidUvSurface() = default;
SolidUvSurface::SolidUvSurface(SurfaceResult surface) {
	Surface = surface;
}

SurfaceResult SolidUvSurface::GetSurface(double u, double v) {
	return Surface;
}
