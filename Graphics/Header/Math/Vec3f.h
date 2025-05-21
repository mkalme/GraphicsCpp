#pragma once
#include "Vec2f.h"
#include <Math.h>

struct Vec3f
{
public:
	double X;
	double Y;
	double Z;

	Vec3f(double x, double y, double z);
	Vec3f(double a);
	Vec3f();

	Vec3f operator +(double a);
	Vec3f operator +(Vec3f const& v);

	Vec3f operator -(double a);
	Vec3f operator -(Vec3f const& v);

	Vec3f operator *(double a);
	Vec3f operator *(Vec3f const& v);

	Vec3f operator /(double a);
	Vec3f operator /(Vec3f const& v);

	bool operator ==(const Vec3f& other) const;
	bool operator !=(const Vec3f& other) const;

	Vec3f Add(double a);
	Vec3f Add(Vec3f const& v);

	Vec3f Sub(double a);
	Vec3f Sub(Vec3f const& v);

	Vec3f Mul(double a);
	Vec3f Mul(Vec3f const& v);

	Vec3f Div(double a);
	Vec3f Div(Vec3f const& v);

	double Dot(Vec3f const& v);
	Vec3f Cross(Vec3f const& v);
	Vec3f Normal();
	Vec3f Inverse();

	double DotItself();
	double Length();
	Vec3f Clamp(double minA, double maxA);
	Vec2f GetXZ();

	bool IsEmpty();
	static Vec3f Empty();
};