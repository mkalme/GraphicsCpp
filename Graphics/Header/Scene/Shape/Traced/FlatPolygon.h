#pragma once
#include "../Object.h"
#include "TriangleMesh.h"
#include "CustomPlaneMesh.h"
#include "../../../Scene/Surface/Flat/FlatSurface.h"

class FlatPolygon : public Object
{
public:
    Vec3f Location;
    double Radius;
    int Sides;

    FlatSurface* Surface;

    FlatPolygon(Vec3f location, double radius, int sides);

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
private:
    double m_sinOfOuterCorner;
    double m_triangleSize;
    CustomPlane m_plane;

    CustomPlaneIntersection IntersectPlane(Ray& const ray);
    bool Validator(Vec2f point);
};