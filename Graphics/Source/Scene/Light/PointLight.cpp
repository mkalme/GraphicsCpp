#include "../../../Header/Scene/Light/PointLight.h"

PointLight::PointLight() = default;
PointLight::PointLight(Vec3f location, double lumens) {
	Location = location;
	Lumens = lumens;
	Color = Vec3f(1);
}
PointLight::PointLight(Vec3f location, double lumens, Vec3f color) {
	Location = location;
	Lumens = lumens;
	Color = color;
}

void PointLight::GetDirectionAndDistance(Vec3f point, Vec3f &direction, double &t) {
	t = (Location - point).Length();
	direction = (Location - point) / t;
}

double PointLight::GetLumens(double distance) {
	return Lumens / (distance * distance);
}