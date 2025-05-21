#include "../../../Header/Gui/FirstPerson/DirectionalInertia.h"
#include <iostream>
#include <mutex>

DirectionalInertia::DirectionalInertia(float maxSpeed, float secondsToMaxSpeed, float secondsToMinSpeed) {
	MaxSpeed = maxSpeed;
	SecondsToMaxSpeed = secondsToMaxSpeed;
	SecondsToMinSpeed = secondsToMinSpeed;
}

void DirectionalInertia::SpeedUp(float secondsPassed, Vec3f direction) {
	float speed_before = CurrentDirection.Length();
	float speed_after = speed_before + (secondsPassed / SecondsToMaxSpeed) * GetRealMaxSpeed();

	if (speed_before > GetRealMaxSpeed()) speed_after = speed_before;

	CurrentDirection = direction * speed_after;

	if (speed_after > GetRealMaxSpeed() && speed_before <= GetRealMaxSpeed()) {
		CurrentDirection = CurrentDirection * (GetRealMaxSpeed() / speed_after);
	}

	lastSpeedUp = std::chrono::system_clock::now();
	lastSpeed = speed_after;
}

void DirectionalInertia::SlowDown() {
	float speed_before = CurrentDirection.Length();
	if (speed_before <= 0) return;

	float seconds_passed = ((std::chrono::system_clock::now() - lastSpeedUp).count() / 10000000.0);

	float speed_after = lastSpeed * ((SecondsToMinSpeed - seconds_passed) / SecondsToMinSpeed);
	if (speed_after <= 0) CurrentDirection = Vec3f(0);
	else CurrentDirection = CurrentDirection * (speed_after / speed_before);
}

Vec3f DirectionalInertia::DistancePassed(float secondsPassed) {
	return CurrentDirection * secondsPassed;
}

float DirectionalInertia::GetRealMaxSpeed() {
	return MaxSpeed * Coefficient;
}