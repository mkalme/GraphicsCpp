#pragma once
#include "../Object.h"
#include "../../../Scene/Surface/Flat/FlatSurface.h"

struct Triangle {
public:
    Vec3f Vertex0;
    Vec3f Vertex1;
    Vec3f Vertex2;
    Vec3f Normal;

    Triangle() = default;
    Triangle(Vec3f vertex0, Vec3f vertex1, Vec3f vertex2) {
        Vertex0 = vertex0;
        Vertex1 = vertex1;
        Vertex2 = vertex2;

        Vec3f a = vertex1 - vertex0;
        Vec3f b = vertex2 - vertex0;
        Normal = a.Cross(b).Normal();
    }
    Triangle(Vec3f vertex0, Vec3f vertex1, Vec3f vertex2, Vec3f normal) {
        Vertex0 = vertex0;
        Vertex1 = vertex1;
        Vertex2 = vertex2;
        Normal = normal;
    }

    double Intersect(Ray& const ray) {
        const double EPSILON = 0.000000001;
        Vec3f edge1, edge2, rayVecXe2, s, sXe1;
        double det, invDet, u, v;
        edge1 = Vertex1 - Vertex0;
        edge2 = Vertex2 - Vertex0;
        rayVecXe2 = ray.Direction.Cross(edge2);
        det = edge1.Dot(rayVecXe2);

        if (det > -EPSILON && det < EPSILON)
            return -1;

        invDet = 1.0 / det;
        s = ray.Origin - Vertex0;
        u = invDet * s.Dot(rayVecXe2);

        if (u < 0.0 || u > 1.0)
            return -1;

        sXe1 = s.Cross(edge1);
        v = invDet * ray.Direction.Dot(sXe1);

        if (v < 0.0 || u + v > 1.0)
            return -1;

        double t = invDet * edge2.Dot(sXe1);

        if (t > EPSILON)
        {
            return t;
        }
        else
            return -1;
    }
};

class TriangleMesh : public Object
{
public:
	Triangle* Triangles = 0;
	int Count = 0;
    bool UseCustomNormals;

	SurfaceResult Surface = SurfaceResult();

	double Intersect(Ray& const ray) override;
	SurfaceIntersection SurfaceIntersect(Ray& const ray) override;
};