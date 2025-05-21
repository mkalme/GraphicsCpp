#pragma once
#include "../Object.h"
#include "../../Surface/SurfaceIntersection.h"
#include "../../Surface/Uv/UvSurface.h"
#include "../../Surface/Uv/SolidUvSurface.h"
#include "../../../Math/Vec3f.h"
#include "../../../Math/Ray.h"

class Sphere : public Object
{
public:
	Vec3f Location;
	double Radius;
	UvSurface* UvSurface = new SolidUvSurface(SurfaceResult(Vec3f(1), 0, 0, 0));

	Sphere();
	Sphere(Vec3f location, double radius);

	double Intersect(Ray& const ray) override;
	SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
	bool Contains(Vec3f point) override;

	static double Intersect(Vec3f location, double radius, Ray& const ray);
private:
	void GetUv(Vec3f n, double& u, double& v);
};