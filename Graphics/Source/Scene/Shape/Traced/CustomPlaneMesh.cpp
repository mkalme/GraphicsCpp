#include "../../../../Header/Scene/Shape/Traced/CustomPlaneMesh.h"
#include "../../../../Header/Math/Vec2f.h"
#include "../../../../Header/Math/Rotation.h"

double CustomPlaneMesh::Intersect(Ray& const ray) {
    double t = -1;

    for (int i = 0; i < Count; i++) {
        CustomPlane triangle = Planes[i];

        CustomPlaneIntersection tt = triangle.Intersect(ray);
        if (tt.T < 0 || (tt.T > t && t > 0)) continue;

        t = tt.T;
    }

    return t;
}

SurfaceIntersection CustomPlaneMesh::SurfaceIntersect(Ray& const ray) {
    double t = -1;
    Vec3f normal;

    for (int i = 0; i < Count; i++) {
        CustomPlane triangle = Planes[i];

        CustomPlaneIntersection tt = triangle.Intersect(ray);
        if (tt.T < 0 || (tt.T > t && t > 0)) continue;

        t = tt.T;
        normal = tt.Normal;
    }

    if (t < 0) return SurfaceIntersection::NoIntersection();

    SurfaceIntersection intersection = SurfaceIntersection(t, normal);
    intersection.Surface = Surface;

    return intersection;

}