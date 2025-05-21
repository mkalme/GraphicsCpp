#pragma once
#include "../Object.h"
#include "../../Surface/SurfaceIntersection.h"
#include "../../Surface/Uv/UvSurface.h"
#include "../../Surface/Uv/SolidUvSurface.h"
#include "../../../Math/Vec3f.h"
#include "../../../Math/Ray.h"
#include "../../../Math/Rotation.h"

class Cone : public Object
{
public:
	Vec3f Location;
	double Radius;
	double Height;

	UvSurface* UvSurface = new SolidUvSurface(SurfaceResult(Vec3f(1), 0, 0, 0));

	double Intersect(Ray& const ray) override;
	SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
	bool Contains(Vec3f point) override;

private:
	bool IntersectWithPlane(Ray& const ray, double &t);
	bool ValidateY(Ray& const ray, double coneT_0, double coneT_1, double& coneT_max, double&);

	void GetUv(Vec3f n, double& u, double& v);
};