#include "../../Header/Math/Rotation.h"
#include "../../Header/Math/Vec3f.h"
#include <cmath>
#include <iostream>

# define _PI           3.14159265358979323846

Rotation::Rotation() = default;
Rotation::Rotation(double radians) {
	Radians = radians;

	_sin = sin(radians);
	_cos = cos(radians);
}

void Rotation::Rotate(double& x, double& y) {
	double xp = x, yp = y;

	x = xp * _cos - yp * _sin;
	y = xp * _sin + yp * _cos;
}

double Rotation::PI() {
	return _PI;
}

Rotation Rotation::FromDegrees(double degrees) {
	return Rotation(degrees * _PI / 180.0);
}

void Rotation::RotateVector(Vec3f &v, Rotation horizontal, Rotation vertical) {
	horizontal.Rotate(v.X, v.Z);

	double hl = sqrt(v.X * v.X + v.Z * v.Z);
	double hl_temp = hl;
	vertical.Rotate(hl, v.Y);

	v.X *= hl / hl_temp;
	v.Z *= hl / hl_temp;
}