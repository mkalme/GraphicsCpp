#pragma once
#include "MarchedObject.h"
#include "../../../Math/Vec3f.h"
#include "../../../Math/Vec2f.h"
#include "../../../Math/Ray.h"
#include "../../../Scene/Surface/SurfaceResult.h"
#include "../../../Scene/Surface/Uv/UvSurface.h"
#include "../../../Scene/Surface/Uv/SolidUvSurface.h"

class MarchedCylinder : public MarchedObject
{
public:
	Vec3f Location;
	double Radius;

	UvSurface* UvSurface = new SolidUvSurface(SurfaceResult(Vec3f(1), 0, 0, 0));

	double GetDistance(Ray& const ray) override;
	void GetNormalAndSurface(Vec3f point, Vec3f& normal, SurfaceResult& surface) override;
	bool Contains(Vec3f point) override;
private:
	Vec2f GetUv(Vec3f n, double y, double r);
};