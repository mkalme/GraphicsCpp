#pragma once
#include "DirectionalInertia.h"
#include "Math/Vec3f.h"

struct Inertia
{
	DirectionalInertia Horizontal = DirectionalInertia(7.5, 0.5, 0.35);
	DirectionalInertia Vertical = DirectionalInertia(7.5, 0.25, 0.25);

	void SetCoefficients(float coefficient);
	Vec3f GetTotalVelocity(float secondsPassed);
};

