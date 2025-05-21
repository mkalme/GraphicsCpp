#include "../../../../Header/Scene/Shape/Traced/Box.h"

Box::Box(Vec3f firstPoint, Vec3f secondPoint) {
	FirstPoint = firstPoint;
	SecondPoint = secondPoint;

	Vec3f p0 = FirstPoint;
	Vec3f p1 = Vec3f(SecondPoint.X, FirstPoint.Y, FirstPoint.Z);
	Vec3f p2 = Vec3f(SecondPoint.X, FirstPoint.Y, SecondPoint.Z);
	Vec3f p3 = Vec3f(FirstPoint.X, FirstPoint.Y, SecondPoint.Z);

	Vec3f p4 = Vec3f(FirstPoint.X, SecondPoint.Y, FirstPoint.Z);
	Vec3f p5 = Vec3f(SecondPoint.X, SecondPoint.Y, FirstPoint.Z);
	Vec3f p6 = Vec3f(SecondPoint.X, SecondPoint.Y, SecondPoint.Z);
	Vec3f p7 = Vec3f(FirstPoint.X, SecondPoint.Y, SecondPoint.Z);

	Triangle* triangles = new Triangle[12] {
		Triangle(p0, p1, p2, Vec3f(0, -1, 0)),
		Triangle(p0, p2, p3, Vec3f(0, -1, 0)),
		Triangle(p4, p5, p6, Vec3f(0, 1, 0)),
		Triangle(p4, p6, p7, Vec3f(0, 1, 0)),

		Triangle(p0, p3, p7, Vec3f(1, 0, 0)),
		Triangle(p0, p4, p7, Vec3f(1, 0, 0)),
		Triangle(p1, p2, p6, Vec3f(-1, 0, 0)),
		Triangle(p1, p5, p6, Vec3f(-1, 0, 0)),

		Triangle(p3, p2, p6, Vec3f(0, 0, 1)),
		Triangle(p3, p7, p6, Vec3f(0, 0, 1)),
		Triangle(p0, p4, p5, Vec3f(0, 0, -1)),
		Triangle(p0, p1, p5, Vec3f(0, 0, -1))
	};

	m_triangleMesh = TriangleMesh();
	m_triangleMesh.Triangles = triangles;
	m_triangleMesh.Count = 12;
	m_triangleMesh.UseCustomNormals = true;
}

double Box::Intersect(Ray& const ray) {
	return m_triangleMesh.Intersect(ray);
}
SurfaceIntersection Box::SurfaceIntersect(Ray& const ray) {
	return m_triangleMesh.SurfaceIntersect(ray);
}

void Box::SetSurface(SurfaceResult surface) {
	m_triangleMesh.Surface = surface;
}

SurfaceResult Box::GetSurface() {
	return m_triangleMesh.Surface;
}

bool Box::Contains(Vec3f point) {
	return IsInRange(point.X, FirstPoint.X, SecondPoint.X)
		&& IsInRange(point.Y, FirstPoint.Y, SecondPoint.Y)
		&& IsInRange(point.Z, FirstPoint.Z, SecondPoint.Z);
}

bool Box::IsInRange(double x, double a, double b) {
	return x > a && x < b || x < a && x > b;
}