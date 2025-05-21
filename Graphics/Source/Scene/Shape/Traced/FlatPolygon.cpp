#include "../../../../Header/Scene/Shape/Traced/FlatPolygon.h"
#include "../../../../Header/Math/Rotation.h"
#include "../../../../Header/Math/MathUtilities.h"
#include "../../../../Header/Scene/Shape/Traced/Prism.h"

FlatPolygon::FlatPolygon(Vec3f location, double radius, int sides) {
	Location = location;
	Radius = radius;
	Sides = sides;

	m_triangleSize = 2 * Rotation::PI() / sides;
	m_sinOfOuterCorner = sin((Rotation::PI() - m_triangleSize) / 2);
	auto validator = [&](Vec2f point) { return Prism::PolygonValidator(point, Radius, m_triangleSize, m_sinOfOuterCorner); };
	m_plane = CustomPlane(Location, Rotation(0), Rotation(0), Vec3f(0, 1, 0), validator);
}

bool FlatPolygon::Validator(Vec2f point) {
	return true;
}

double FlatPolygon::Intersect(Ray& const ray) {
	return IntersectPlane(ray).T;
}

SurfaceIntersection FlatPolygon::SurfaceIntersect(Ray& const ray) {
	CustomPlaneIntersection intersection = IntersectPlane(ray);
	if (intersection.T < 0) return SurfaceIntersection::NoIntersection();

	SurfaceIntersection output = SurfaceIntersection(intersection.T, m_plane.Normal);
	output.Surface = Surface->GetSurface(intersection.Coords.X, intersection.Coords.Y);

	return output;
}

CustomPlaneIntersection FlatPolygon::IntersectPlane(Ray& const ray) {
	return m_plane.Intersect(ray);
}