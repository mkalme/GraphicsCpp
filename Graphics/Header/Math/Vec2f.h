#pragma once
#include <Math.h>

struct Vec2f
{
public:
	double X;
	double Y;

	Vec2f(double x, double y);
	Vec2f(double a);
	Vec2f();

	Vec2f operator +(double a);
	Vec2f operator +(Vec2f const& v);

	Vec2f operator -(double a);
	Vec2f operator -(Vec2f const& v);

	Vec2f operator *(double a);
	Vec2f operator *(Vec2f const& v);

	Vec2f operator /(double a);
	Vec2f operator /(Vec2f const& v);

	bool operator ==(const Vec2f& other) const;
	bool operator !=(const Vec2f& other) const;

	Vec2f Add(double a);
	Vec2f Add(Vec2f const& v);

	Vec2f Sub(double a);
	Vec2f Sub(Vec2f const& v);

	Vec2f Mul(double a);
	Vec2f Mul(Vec2f const& v);

	Vec2f Div(double a);
	Vec2f Div(Vec2f const& v);

	double Dot(Vec2f const& v);
	Vec2f Normal();
	Vec2f Inverse();

	double DotItself();
	double Length();
	Vec2f Clamp(double minA, double maxA);

	bool IsEmpty();
	static Vec2f Empty();
};