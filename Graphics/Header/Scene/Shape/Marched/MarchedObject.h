#pragma once
#include "../Object.h"

class MarchedObject : public Object
{
public:
    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;
    
    virtual double GetDistance(Ray& const ray);
    virtual void GetNormalAndSurface(Vec3f point, Vec3f &normal, SurfaceResult &surface);
protected:
    int MaxSteps = 10000;
};