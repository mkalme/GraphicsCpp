#pragma once
#include "../Object.h"
#include "../../../Scene/Surface/Uv/UvSurface.h"
#include "../../../Math/Vec2f.h"
#include "../../../Math/Rotation.h"

class Cylinder : public Object
{
public:
	Vec3f Location;
	double Radius;
	UvSurface* Surface;

	Cylinder();
	Cylinder(Vec3f location, double radius, UvSurface* surface);

	double Intersect(Ray& const ray) override;
	SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
	bool Contains(Vec3f point) override;
private:
	Vec2f GetUV(Vec3f n, double y, double r);
};

