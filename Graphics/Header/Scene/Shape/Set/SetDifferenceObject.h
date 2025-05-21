#pragma once
#include "../Object.h"
#include <vector>

class SetDifferenceObject : public Object
{
public:
    Object* MainObject;
    std::vector<Object*> Difference;

    SetDifferenceObject(Object* mainObject, std::vector<Object*> difference);

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;
private:
    double IntersectDifference(Ray& const ray, Object* &ignore);
    SurfaceIntersection SurfaceIntersectDifference(Ray& const ray, Object* &ignore);
    bool ContainsDifference(Vec3f point, Object* ignore);
};