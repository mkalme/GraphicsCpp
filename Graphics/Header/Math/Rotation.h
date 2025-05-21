#pragma once
#include "Vec3f.h"

struct Rotation
{
public:
	double Radians;

	Rotation();
	Rotation(double radians);

	void Rotate(double &x, double &y);

	static double PI();
	static Rotation FromDegrees(double degrees);
	static void RotateVector(Vec3f &v, Rotation horizontal, Rotation vertical);
private:
	double _sin;
	double _cos;
};