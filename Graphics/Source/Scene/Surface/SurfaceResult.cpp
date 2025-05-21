#include "../../../Header/Scene/Surface/SurfaceResult.h"

SurfaceResult::SurfaceResult() {
	Color = Vec3f(0);
	ReflectionIndex = 0;
	FresnelIndex = 0;
	SpecularPow = 0;
}
SurfaceResult::SurfaceResult(Vec3f color, double reflectionIndex, double fresnelIndex, double specularPow) {
	Color = color;
	ReflectionIndex = reflectionIndex;
	FresnelIndex = fresnelIndex;
	SpecularPow = specularPow;
}