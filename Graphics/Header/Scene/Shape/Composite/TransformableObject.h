#pragma once
#include "../Object.h"
#include "../../../Math/Rotation.h"
#include "../../../Math/Vec2f.h"

class TransformableObject : public Object
{
public:
    Object* Object;

    Vec3f RotationalPoint;
    Vec3f Offset;

    double Intersect(Ray& const ray) override;
    SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
    bool Contains(Vec3f point) override;

    Rotation GetHorizontalRotation();
    void SetHorizontalRotation(Rotation rotation);

    Rotation GetVerticalRotation();
    void SetVerticalRotation(Rotation rotation);

    Vec2f GetVerticalAxis();
    void SetVerticalAxis(Vec2f axis);
private:
    Rotation m_horizontalRotation;
    Rotation m_horizontalRotationOpposite;

    Rotation m_verticalRotation;
    Rotation m_verticalRotationOpposite;

    Rotation m_verticalAxisRotation;
    Rotation m_verticalAxisRotationOpposite;
    Vec2f m_verticalAxis;

    Ray CreateNewRay(Ray& const ray);
    Vec3f RotatePoint(Vec3f point);
    Vec3f RotateVertically(Vec3f point, bool inverse);
};