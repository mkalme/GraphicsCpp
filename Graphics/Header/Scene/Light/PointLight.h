#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	Vec3f Location;
	double Lumens;

	PointLight();
	PointLight(Vec3f location, double lumens);
	PointLight(Vec3f location, double lumens, Vec3f color);

	void GetDirectionAndDistance(Vec3f point, Vec3f& direction, double& t) override;
	double GetLumens(double distance) override;
};

