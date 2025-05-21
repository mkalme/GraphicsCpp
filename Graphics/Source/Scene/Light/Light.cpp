#include "../../../Header/Scene/Light/Light.h"

void Light::GetDirectionAndDistance(Vec3f point, Vec3f& direction, double& t) {
	direction = Vec3f(0);
	t = 0;
}

double Light::GetLumens(double distance) {
	return 0;
}