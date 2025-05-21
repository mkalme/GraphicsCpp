#pragma once
#include "Sky.h"

class SolidColorSky : public Sky
{
public:
	Vec3f Color;

	SolidColorSky();
	SolidColorSky(Vec3f color);

	Vec3f GetColor(Vec3f direction) override;
};

