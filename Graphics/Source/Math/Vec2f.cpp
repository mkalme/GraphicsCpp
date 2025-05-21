#include "../../Header/Math/Vec2f.h"
#include <cmath>
#include <Math.h>

Vec2f::Vec2f(double x, double y) {
	X = x;
	Y = y;
}
Vec2f::Vec2f(double a) {
	X = a;
	Y = a;
}
Vec2f::Vec2f() = default;

Vec2f Vec2f::operator +(double a)
{
	return Add(a);
}
Vec2f Vec2f::operator +(Vec2f const& v)
{
	return Add(v);
}

Vec2f Vec2f::operator -(double a)
{
	return Sub(a);
}
Vec2f Vec2f::operator -(Vec2f const& v)
{
	return Sub(v);
}

Vec2f Vec2f::operator *(double a)
{
	return Mul(a);
}
Vec2f Vec2f::operator *(Vec2f const& v)
{
	return Mul(v);
}

Vec2f Vec2f::operator /(double a)
{
	return Div(a);
}
Vec2f Vec2f::operator /(Vec2f const& v)
{
	return Div(v);
}

bool Vec2f::operator ==(const Vec2f& other) const
{
	return X == other.X && Y == other.Y;
}
bool Vec2f::operator !=(const Vec2f& other) const
{
	return X != other.X || Y != other.Y;
}

Vec2f Vec2f::Add(double a) {
	return Vec2f(X + a, Y + a);
}
Vec2f Vec2f::Add(Vec2f const& v) {
	return Vec2f(X + v.X, Y + v.Y);
}

Vec2f Vec2f::Sub(double a) {
	return Vec2f(X - a, Y - a);
}
Vec2f Vec2f::Sub(Vec2f const& v) {
	return Vec2f(X - v.X, Y - v.Y);
}

Vec2f Vec2f::Mul(double a) {
	return Vec2f(X * a, Y * a);
}
Vec2f Vec2f::Mul(Vec2f const& v) {
	return Vec2f(X * v.X, Y * v.Y);
}

Vec2f Vec2f::Div(double a) {
	return Vec2f(X / a, Y / a);
}
Vec2f Vec2f::Div(Vec2f const& v) {
	return Vec2f(X / v.X, Y / v.Y);
}

double Vec2f::Dot(Vec2f const& v) {
	return X * v.X + Y * v.Y;
}
Vec2f Vec2f::Normal() {
	double l = Length();
	if (l == 0) return Vec2f(0);

	return Vec2f(X / l, Y / l);
}
Vec2f Vec2f::Inverse() {
	return Vec2f(-X, -Y);
}

double Vec2f::DotItself() {
	return X * X + Y * Y;
}
double Vec2f::Length() {
	return sqrt(DotItself());
}
Vec2f Vec2f::Clamp(double minA, double maxA) {
	double x = X, y = Y;

	if (x < minA) x = minA;
	else if (x > maxA) x = maxA;

	if (y < minA) y = minA;
	else if (y > maxA) y = maxA;

	return Vec2f(x, y);
}

bool Vec2f::IsEmpty() {
	return isnan(X) && isnan(Y);
}
Vec2f Vec2f::Empty() {
	return Vec2f(NAN, NAN);
}