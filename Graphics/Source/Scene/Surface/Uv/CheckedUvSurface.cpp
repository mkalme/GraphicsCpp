#include "../../../../Header/Scene/Surface/Uv/CheckedUvSurface.h"

SurfaceResult CheckedUvSurface::GetSurface(double u, double v) {
	int uu = (int)floor(u / SquareSize_U);
	int vv = (int)floor(v / SquareSize_V);

	return ((int)floor(uu) % 2 == 0) ^ ((int)floor(vv) % 2 == 0) ? FirstCell : SecondCell;
}