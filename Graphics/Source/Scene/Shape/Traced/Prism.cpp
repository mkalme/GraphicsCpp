#include "../../../../Header/Scene/Shape/Traced/Prism.h"
#include "../../../../Header/Math/MathUtilities.h"

Prism::Prism(Vec3f location, double height, double radius, int sides) {
	Location = location;
	Height = height;
	Radius = radius;
	Sides = sides;

	CustomPlane* planes = new CustomPlane[Sides + 2];

	double pointAngle = Rotation::PI() / sides;
	double triangleCorner = (Rotation::PI() - pointAngle * 2) / 2;
	double angleB = Rotation::PI() - triangleCorner - pointAngle * 2;
	m_sinOfOuterCorner = sin((Rotation::PI() - pointAngle * 2) / 2);
	double length = Radius / sin(angleB) * m_sinOfOuterCorner;
	m_triangleOuterLength = sqrt(Radius * Radius + Radius * Radius - 2 * Radius * Radius * cos(pointAngle * 2));
	m_triangleSize = pointAngle * 2;

	double turnBy = (Rotation::PI() / 2) - (Rotation::PI() - m_triangleSize) / 2;

	auto rectangleValidator = [&](Vec2f point) { return RectangleValidator(point); };

	Rotation rotation = Rotation(-pointAngle);
	Vec2f point = Vec2f(0, Radius);

	for (int i = 0; i < Sides; i++) {
		Vec3f vertex0 = Vec3f(point.X, 0, point.Y);
		rotation.Rotate(point.X, point.Y);

		Vec3f normal = Vec3f(point.X, 0, point.Y) / Radius;
		rotation.Rotate(point.X, point.Y);

		double hAngle = Rotation::PI() + turnBy + turnBy * 2 * i;;
		planes[i + 2] = CustomPlane(vertex0 + location, Rotation(-Rotation::PI() / 2), Rotation(hAngle), normal, rectangleValidator);
	}

	auto validator = [&](Vec2f point) { return Prism::PolygonValidator(point, Radius, m_triangleSize, m_sinOfOuterCorner); };

	planes[0] = CustomPlane(Location, Rotation(0), Rotation(0), Vec3f(0, -1, 0), validator);
	planes[1] = CustomPlane(Location + Vec3f(0, Height, 0), Rotation(0), Rotation(0), Vec3f(0, 1, 0), validator);

	m_planeMesh = CustomPlaneMesh();
	m_planeMesh.Planes = planes;
	m_planeMesh.Count = Sides + 2;
	m_planeMesh.UseCustomNormals = true;
}

double Prism::Intersect(Ray& const ray) {
	return m_planeMesh.Intersect(ray);
}

SurfaceIntersection Prism::SurfaceIntersect(Ray& const ray) {
	return m_planeMesh.SurfaceIntersect(ray);
}

bool Prism::Contains(Vec3f point) {
	if (!PolygonValidator(Vec2f(-(point.X - Location.X), point.Z - Location.Z), Radius, m_triangleSize, m_sinOfOuterCorner)) return false;
	return point.Y >= Location.Y && point.Y <= Location.Y + Height;
}

bool Prism::RectangleValidator(Vec2f point) {
	return point.X >= 0 && point.X <= m_triangleOuterLength && point.Y >= 0 && point.Y <= Height;
}

bool Prism::PolygonValidator(Vec2f point, double radius, double triangleSize, double sinOfOuterCorner) {
	double distanceFromCenterSquared = point.DotItself();
	if (distanceFromCenterSquared > radius * radius) return false;

	double pointAngle = atan2(point.X, point.Y);
	pointAngle = MathUtilities::NegMod(pointAngle, triangleSize);

	double b = (Rotation::PI() - triangleSize) / 2;
	double a = Rotation::PI() - pointAngle - b;
	double length = radius / sin(a) * sinOfOuterCorner;

	return distanceFromCenterSquared <= length * length;
}

void Prism::SetSurface(SurfaceResult surface) {
	m_planeMesh.Surface = surface;
}

SurfaceResult Prism::GetSurface() {
	return m_planeMesh.Surface;
}