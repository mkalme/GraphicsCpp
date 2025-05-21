#pragma once
#include "../Surface/SurfaceIntersection.h"
#include "../../Math/Ray.h"

class Object
{
public:
	virtual double Intersect(Ray& const ray);
	virtual SurfaceIntersection SurfaceIntersect(Ray& const ray);
	virtual bool Contains(Vec3f point);
};