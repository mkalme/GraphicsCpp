#pragma once
#include "../Object.h"
#include "../../../Scene/Surface/Flat/FlatSurface.h"
#include "CustomPlaneMesh.h"
#include "TriangleMesh.h"

class Pyramid : public Object
{
public:
    Vec3f Location;
    double Height;
    double Radius;
    int Sides;

    Pyramid(Vec3f location, double height, double radius, int sides);

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;

    void SetSurface(SurfaceResult surface);
    SurfaceResult GetSurface();
private:
    CustomPlane m_plane;
    TriangleMesh m_triangleMesh;
    double m_triangleOuterLength = 0;
    double m_sinOfOuterCorner;
    double m_triangleSize;
};