#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	Vec3f DirectionInSky;
	double Lumens;

	DirectionalLight();
	DirectionalLight(Vec3f directionInSky, double lumens);
	DirectionalLight(Vec3f directionInSky, double lumens, Vec3f color);

	void GetDirectionAndDistance(Vec3f point, Vec3f& direction, double& t) override;
	double GetLumens(double distance) override;
};

