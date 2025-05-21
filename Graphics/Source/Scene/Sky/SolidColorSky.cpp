#include "../../../Header/Scene/Sky/SolidColorSky.h"

SolidColorSky::SolidColorSky() = default;
SolidColorSky::SolidColorSky(Vec3f color) {
	Color = color;
}

Vec3f SolidColorSky::GetColor(Vec3f direction) {
	return Color;
}