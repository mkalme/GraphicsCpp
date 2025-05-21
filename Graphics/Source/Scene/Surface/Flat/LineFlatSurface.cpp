#include "../../../../Header/Scene/Surface/Flat/LineFlatSurface.h"
#include "../../../../Header/Math/MathUtilities.h"

SurfaceResult LineFlatSurface::GetSurface(double x, double y) {
	x += Offset;
	double mod = MathUtilities::NegMod(x, FirstLineWidth + SecondLineWidth);

	if (mod <= FirstLineWidth) return FirstSurfaceResult;
	return SecondSurfaceResult;
}