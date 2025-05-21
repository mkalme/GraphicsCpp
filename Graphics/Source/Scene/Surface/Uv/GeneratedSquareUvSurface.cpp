#include "../../../../Header/Scene/Surface/Uv/GeneratedSquareUvSurface.h"

size_t Hash(int a, int b);

GeneratedSquareUvSurface::GeneratedSquareUvSurface() = default;
GeneratedSquareUvSurface::GeneratedSquareUvSurface(Vec3f firstColor, Vec3f secondColor, SurfaceResult defaultSurface) {
	FirstColor = firstColor;
	SecondColor = secondColor;
	DefaultSurface = defaultSurface;
}

SurfaceResult GeneratedSquareUvSurface::GetSurface(double u, double v) {
	int uu = (int)floor(u / SquareSize_U);
	int vv = (int)floor(v / SquareSize_V);

	size_t hash = Hash(uu, vv);
	double intensity = (hash % 1000) / 1000.0;

	Vec3f color = FirstColor * (1 - intensity) + SecondColor * intensity;
	color = color.Clamp(0, 1);

	SurfaceResult output = DefaultSurface;
	output.Color = color;

	return output;
}

size_t Hash(int a, int b) {
	size_t h = (size_t(a) << 32) + size_t(b);
	h *= 1231231557ull;
	h ^= (h >> 32);
	return h;
}