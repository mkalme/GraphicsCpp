#pragma once
#include "../../Math/Vec3f.h"

class Light
{
public:
	Vec3f Color;

	virtual void GetDirectionAndDistance(Vec3f point, Vec3f &direction, double &t);
	virtual double GetLumens(double distance);
};

