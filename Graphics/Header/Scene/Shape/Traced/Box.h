#pragma once
#include "../Object.h"
#include "../../../Scene/Surface/Flat/FlatSurface.h"
#include "TriangleMesh.h"

class Box : public Object
{
public:
    Vec3f FirstPoint;
    Vec3f SecondPoint;

    Box(Vec3f firstPoint, Vec3f secondPoint);

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;

    void SetSurface(SurfaceResult surface);
    SurfaceResult GetSurface();
private:
    TriangleMesh m_triangleMesh;

    bool IsInRange(double x, double a, double b);
};