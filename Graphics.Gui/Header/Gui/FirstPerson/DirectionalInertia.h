#pragma once
#include "Math/Vec3f.h"
#include <corecrt_math.h>
#include <mutex>

struct DirectionalInertia {
	float MaxSpeed;
	float SecondsToMaxSpeed;
	float SecondsToMinSpeed;
	float Coefficient = 1;

	Vec3f CurrentDirection = Vec3f(0);

	DirectionalInertia(float maxSpeed, float secondsToMaxSpeed, float secondsToMinSpeed);

	void SpeedUp(float secondsPassed, Vec3f direction);
	void SlowDown();
	Vec3f DistancePassed(float secondsPassed);
private:
	std::chrono::system_clock::time_point lastSpeedUp = std::chrono::system_clock::now();
	float lastSpeed = 0;
	float GetRealMaxSpeed();
};