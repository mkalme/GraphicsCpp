#include "../../../../Header/Scene/Shape/Composite/TransformableObject.h"
#include <stdlib.h>
#include <iostream>

double TransformableObject::Intersect(Ray& const ray) {
    Ray newRay = CreateNewRay(ray);
    return Object->Intersect(newRay);
}

SurfaceIntersection TransformableObject::SurfaceIntersect(Ray& const ray) {
    Ray newRay = CreateNewRay(ray);
    SurfaceIntersection intersection = Object->SurfaceIntersect(newRay);

    Vec3f direction = intersection.Normal;
    m_horizontalRotationOpposite.Rotate(direction.X, direction.Z);
    direction = RotateVertically(direction, true);
    intersection.Normal = direction;

    return intersection;
}

bool TransformableObject::Contains(Vec3f point) {
    return Object->Contains(RotatePoint(point) - Offset);
}

Ray TransformableObject::CreateNewRay(Ray& const ray) {
    Vec3f origin = RotatePoint(ray.Origin);

    Vec3f direction = ray.Direction;
    direction = RotateVertically(direction, false);
    m_horizontalRotation.Rotate(direction.X, direction.Z);

    return Ray(origin, direction);
}

Vec3f TransformableObject::RotatePoint(Vec3f point) {
    Vec3f origin = point - RotationalPoint - Offset;
    origin = RotateVertically(origin, false);
    m_horizontalRotation.Rotate(origin.X, origin.Z);

    return origin + RotationalPoint;
}

Vec3f TransformableObject::RotateVertically(Vec3f point, bool inverse) {
    if (m_verticalRotation.Radians == 0) return point;

    Rotation forward = m_verticalAxisRotation, backward = m_verticalAxisRotationOpposite, axis = m_verticalRotation;
    if (inverse) {
        forward = m_verticalAxisRotation;
        backward = m_verticalAxisRotationOpposite;
        axis = m_verticalRotationOpposite;
    }

    Vec3f transformed = point;
    forward.Rotate(transformed.X, transformed.Z);

    double px = transformed.Z, py = transformed.Y;
    double hl_temp = px;
    axis.Rotate(px, transformed.Y);
    transformed.Z *= px / hl_temp;

    backward.Rotate(transformed.X, transformed.Z);
    return transformed;
}

Rotation TransformableObject::GetHorizontalRotation() {
    return m_horizontalRotation;
}

void TransformableObject::SetHorizontalRotation(Rotation rotation) {
    m_horizontalRotation = rotation;
    m_horizontalRotationOpposite = Rotation(-rotation.Radians);
}

Rotation TransformableObject::GetVerticalRotation() {
    return m_verticalRotation;
}

void TransformableObject::SetVerticalRotation(Rotation rotation) {
    m_verticalRotation = rotation;
    m_verticalRotationOpposite = Rotation(-rotation.Radians);
}

Vec2f TransformableObject::GetVerticalAxis() {
    return m_verticalAxis;
}

void TransformableObject::SetVerticalAxis(Vec2f axis) {
    m_verticalAxis = axis;
    m_verticalAxisRotation = Rotation(atan2(axis.Y, axis.X));
    m_verticalAxisRotationOpposite = Rotation(-atan2(axis.Y, axis.X));
}