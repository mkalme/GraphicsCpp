#include "../../../../Header/Scene/Shape/Traced/TriangleMesh.h"
#include "../../../../Header/Math/Vec2f.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/Ray.h"

double TriangleMesh::Intersect(Ray& const ray) {
    double t = -1;

    for (int i = 0; i < Count; i++) {
        Triangle triangle = Triangles[i];

        double tt = triangle.Intersect(ray);
        if (tt < 0 || (tt > t && t > 0)) continue;

        t = tt;
    }

    return t;
}

SurfaceIntersection TriangleMesh::SurfaceIntersect(Ray& const ray) {
    double t = -1;
    Vec3f normal;

    for (int i = 0; i < Count; i++) {
        Triangle triangle = Triangles[i];

        double tt = triangle.Intersect(ray);
        if (tt < 0 || (tt > t && t > 0)) continue;

        t = tt;
        normal = triangle.Normal;
    }

    if (t < 0) return SurfaceIntersection::NoIntersection();

    SurfaceIntersection intersection = SurfaceIntersection(t, normal);
    intersection.Surface = Surface;

    return intersection;

}