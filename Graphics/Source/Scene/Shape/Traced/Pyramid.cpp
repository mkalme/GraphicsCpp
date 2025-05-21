#include "../../../../Header/Scene/Shape/Traced/Pyramid.h"
#include "../../../../Header/Scene/Shape/Traced/Prism.h"

Pyramid::Pyramid(Vec3f location, double height, double radius, int sides) {
	Location = location;
	Height = height;
	Radius = radius;
	Sides = sides;

	Triangle* triangles = new Triangle[Sides];

	double pointAngle = Rotation::PI() / sides;
	double triangleCorner = (Rotation::PI() - pointAngle * 2) / 2;
	double angleB = Rotation::PI() - triangleCorner - pointAngle * 2;
	m_sinOfOuterCorner = sin((Rotation::PI() - pointAngle * 2) / 2);
	double length = Radius / sin(angleB) * m_sinOfOuterCorner;
	m_triangleOuterLength = sqrt(Radius * Radius + Radius * Radius - 2 * Radius * Radius * cos(pointAngle * 2));
	m_triangleSize = pointAngle * 2;

	double turnBy = (Rotation::PI() / 2) - (Rotation::PI() - m_triangleSize) / 2;
	Rotation rotation = Rotation(-pointAngle);
	Vec2f point = Vec2f(0, Radius);

	for (int i = 0; i < Sides; i++) {
		Vec3f vertex0 = Vec3f(point.X, 0, point.Y);
		rotation.Rotate(point.X, point.Y);

		rotation.Rotate(point.X, point.Y);
		Vec3f vertex1 = Vec3f(point.X, 0, point.Y);

		triangles[i] = Triangle(vertex0 + Location, vertex1 + Location, Location + Vec3f(0, Height, 0));
		if (triangles[i].Normal.Y < 0) triangles[i].Normal = triangles[i].Normal.Inverse();
	}

	m_triangleMesh = TriangleMesh();
	m_triangleMesh.Triangles = triangles;
	m_triangleMesh.Count = Sides;
	m_triangleMesh.UseCustomNormals = true;

	auto validator = [&](Vec2f point) { return Prism::PolygonValidator(point, Radius, m_triangleSize, m_sinOfOuterCorner); };
	m_plane = CustomPlane(Location, Rotation(0), Rotation(0), Vec3f(0, -1, 0), validator);
}

double Pyramid::Intersect(Ray& const ray) {
	double t1 = m_triangleMesh.Intersect(ray);
	double t2 = m_plane.Intersect(ray).T;

	if (t1 < 0) return t2;
	else if (t2 < 0) return t1;
	return fmin(t1, t2);
}

SurfaceIntersection Pyramid::SurfaceIntersect(Ray& const ray) {
	SurfaceIntersection t1 = m_triangleMesh.SurfaceIntersect(ray);
	CustomPlaneIntersection t2 = m_plane.Intersect(ray);

	if (t2.T < 0 || (t1.T >= 0 && t1.T < t2.T)) {
		return t1;
	}

	SurfaceIntersection output = SurfaceIntersection(t2.T, t2.Normal);
	output.Surface = m_triangleMesh.Surface;

	return output;
}

bool Pyramid::Contains(Vec3f point) {
	if (point.Y < Location.Y || point.Y > Location.Y + Height) return false;
	return Prism::PolygonValidator(Vec2f(-(point.X - Location.X), point.Z - Location.Z), Radius * (1 - ((point.Y - Location.Y) / Height)), m_triangleSize, m_sinOfOuterCorner);
}

void Pyramid::SetSurface(SurfaceResult surface) {
	m_triangleMesh.Surface = surface;
}

SurfaceResult Pyramid::GetSurface() {
	return m_triangleMesh.Surface;
}
