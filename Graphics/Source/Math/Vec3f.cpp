#include "../../Header/Math/Vec3f.h"
#include <cmath>
#include <Math.h>

Vec3f::Vec3f(double x, double y, double z) {
	X = x;
	Y = y;
	Z = z;
}
Vec3f::Vec3f(double a) {
	X = a;
	Y = a;
	Z = a;
}
Vec3f::Vec3f() = default;

Vec3f Vec3f::operator +(double a)
{
	return Add(a);
}

Vec3f Vec3f::operator +(Vec3f const& v)
{
	return Add(v);
}

Vec3f Vec3f::operator -(double a)
{
	return Sub(a);
}

Vec3f Vec3f::operator -(Vec3f const& v)
{
	return Sub(v);
}

Vec3f Vec3f::operator *(double a)
{
	return Mul(a);
}

Vec3f Vec3f::operator *(Vec3f const& v)
{
	return Mul(v);
}

Vec3f Vec3f::operator /(double a)
{
	return Div(a);
}

Vec3f Vec3f::operator /(Vec3f const& v)
{
	return Div(v);
}

bool Vec3f::operator ==(const Vec3f& other) const
{
	return X == other.X && Y == other.Y && Z == other.Z;
}

bool Vec3f::operator !=(const Vec3f& other) const
{
	return X != other.X || Y != other.Y || Z != other.Z;
}

Vec3f Vec3f::Add(double a) {
	return Vec3f(X + a, Y + a, Z + a);
}

Vec3f Vec3f::Add(Vec3f const& v) {
	return Vec3f(X + v.X, Y + v.Y, Z + v.Z);
}

Vec3f Vec3f::Sub(double a) {
	return Vec3f(X - a, Y - a, Z - a);
}

Vec3f Vec3f::Sub(Vec3f const& v) {
	return Vec3f(X - v.X, Y - v.Y, Z - v.Z);
}

Vec3f Vec3f::Mul(double a) {
	return Vec3f(X * a, Y * a, Z * a);
}

Vec3f Vec3f::Mul(Vec3f const& v) {
	return Vec3f(X * v.X, Y * v.Y, Z * v.Z);
}

Vec3f Vec3f::Div(double a) {
	return Vec3f(X / a, Y / a, Z / a);
}

Vec3f Vec3f::Div(Vec3f const& v) {
	return Vec3f(X / v.X, Y / v.Y, Z / v.Z);
}

double Vec3f::Dot(Vec3f const& v) {
	return X * v.X + Y * v.Y + Z * v.Z;
}

Vec3f Vec3f::Cross(Vec3f const& v) {
	double x = Y * v.Z - Z * v.Y;
	double y = -(X * v.Z - Z * v.X);
	double z = X * v.Y - Y * v.X;

	return Vec3f(x, y, z);
}

Vec3f Vec3f::Normal() {
	double l = Length();
	if (l == 0) return Vec3f(0);

	return Vec3f(X / l, Y / l, Z / l);
}

Vec3f Vec3f::Inverse() {
	return Vec3f(-X, -Y, -Z);
}

double Vec3f::DotItself() {
	return X * X + Y * Y + Z * Z;
}

double Vec3f::Length() {
	return sqrt(DotItself());
}

Vec3f Vec3f::Clamp(double minA, double maxA) {
	double x = X, y = Y, z = Z;

	if (x < minA) x = minA;
	else if (x > maxA) x = maxA;

	if (y < minA) y = minA;
	else if (y > maxA) y = maxA;

	if (z < minA) z = minA;
	else if (z > maxA) z = maxA;

	return Vec3f(x, y, z);
}

Vec2f Vec3f::GetXZ() {
	return Vec2f(X, Z);
}

bool Vec3f::IsEmpty() {
	return isnan(X) && isnan(Y) && isnan(Z);
}

Vec3f Vec3f::Empty() {
	return Vec3f(NAN, NAN, NAN);
}