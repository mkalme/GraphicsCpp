#include "../../../Header/Gui/FirstPerson/Inertia.h"

void Inertia::SetCoefficients(float coefficient) {
	Horizontal.Coefficient = coefficient;
	Vertical.Coefficient = coefficient;
}

Vec3f Inertia::GetTotalVelocity(float secondsPassed) {
	return Horizontal.DistancePassed(secondsPassed) + Vertical.DistancePassed(secondsPassed);
}