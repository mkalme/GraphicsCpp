#pragma once
#include "../Object.h"
#include "../../../Scene/Surface/Flat/FlatSurface.h"
#include "CustomPlaneMesh.h"

class Prism : public Object
{
public:
    Vec3f Location;
    double Height;
    double Radius;
    int Sides;

    Prism(Vec3f location, double height, double radius, int sides);

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;

    void SetSurface(SurfaceResult surface);
    SurfaceResult GetSurface();

    static bool PolygonValidator(Vec2f point, double radius, double triangleSize, double sinOfOuterCorner);
private:
    CustomPlaneMesh m_planeMesh;
    double m_triangleOuterLength = 0;
    double m_sinOfOuterCorner;
    double m_triangleSize;

    bool RectangleValidator(Vec2f point);
};