#pragma once
#include "../Object.h"
#include <vector>

class UnionObject : public Object
{
public:
    std::vector<Object*> Objects;

    UnionObject(std::vector<Object*> objects);

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;
};