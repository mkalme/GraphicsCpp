#include "../../../Header/Scene/Light/DirectionalLight.h"
#include <limits>

DirectionalLight::DirectionalLight() = default;
DirectionalLight::DirectionalLight(Vec3f directionInSky, double lumens) {
	DirectionInSky = directionInSky;
	Lumens = lumens;
	Color = Vec3f(1);
}
DirectionalLight::DirectionalLight(Vec3f directionInSky, double lumens, Vec3f color) {
	DirectionInSky = directionInSky;
	Lumens = lumens;
	Color = color;
}

void DirectionalLight::GetDirectionAndDistance(Vec3f point, Vec3f& direction, double& t) {
	direction = DirectionInSky;
	t = std::numeric_limits<double>::max();
}

double DirectionalLight::GetLumens(double distance) {
	return Lumens;
}