#pragma once
#include "../../../Header/Math/Vec3f.h"

class Fog
{
public:
	virtual void GetColorAndIntensity(double t, Vec3f &color, double &intensity);
};