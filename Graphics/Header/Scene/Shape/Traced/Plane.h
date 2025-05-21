#pragma once
#include "../Object.h"
#include "../../Surface/SurfaceIntersection.h"
#include "../../Surface/Flat/FlatSurface.h"
#include "../../Surface/Flat/SolidFlatSurface.h"
#include "../../../Math/Rotation.h"
#include "../../../Math/Vec3f.h"
#include "../../../Math/Ray.h"

class Plane : public Object
{
public:
	Vec3f Origin;
	Vec3f Normal;

	FlatSurface* Surface = new SolidFlatSurface();

	Plane();
	Plane(Vec3f origin, Vec3f normal);

	double Intersect(Ray& const ray);
	SurfaceIntersection SurfaceIntersect(Ray& const ray);

	static double Intersect(Vec3f origin, Vec3f normal, Ray& const ray);
private:
	Rotation m_xRotation;
	Rotation m_zRotation;

	void TransformPoint(Vec3f point, double& x, double& y);
};

