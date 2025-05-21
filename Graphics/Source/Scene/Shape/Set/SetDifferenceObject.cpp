#include "../../../../Header/Scene/Shape/Set/SetDifferenceObject.h"

SetDifferenceObject::SetDifferenceObject(Object* mainObject, std::vector<Object*> difference) {
	MainObject = mainObject;
	Difference = difference;
}

double SetDifferenceObject::Intersect(Ray& const ray) {
	Vec3f o = ray.Origin;
	Object* ignore = nullptr;
	double tt = 0;
	int prevScenario = -1;

	while (true) {
		bool insideMain = prevScenario == 0 || MainObject->Contains(o);
		bool insideDiff = ContainsDifference(o, ignore);

		if (prevScenario == 2 && insideMain && !insideDiff) return tt;
		if (prevScenario == 0 && !insideDiff) return tt;

		int scenario;
		if (!insideMain) scenario = 0;
		else if (!insideDiff) scenario = 1;
		else scenario = 2;

		Ray newRay = Ray(o, ray.Direction);
		double t = -1;
		ignore = nullptr;

		if (scenario == 0) {
			t = MainObject->Intersect(newRay);
		}else if (scenario == 1) {
			double mainT = MainObject->Intersect(newRay);
			double diffT = IntersectDifference(newRay, ignore);

			if (diffT < 0) return tt + mainT;
			return tt + fmin(mainT, diffT);
		}else {
			t = IntersectDifference(newRay, ignore);
		}

		if (t < 0) return -1;
		o = o + ray.Direction * (t * 1.000001);
		tt += t;
		prevScenario = scenario;
	}
}

SurfaceIntersection SetDifferenceObject::SurfaceIntersect(Ray& const ray) {
	Vec3f o = ray.Origin;
	Object* ignore = nullptr;
	SurfaceIntersection lastSurface;
	double tt = 0;
	int prevScenario = -1;

	while (true) {
		bool insideMain = prevScenario == 0 || MainObject->Contains(o);
		bool insideDiff = ContainsDifference(o, ignore);

		if (prevScenario == 2 && insideMain && !insideDiff) {
			lastSurface.T = tt;
			return lastSurface;
		}
		if (prevScenario == 0 && !insideDiff) {
			lastSurface.T = tt;
			return lastSurface;
		}

		int scenario;
		if (!insideMain) scenario = 0;
		else if (!insideDiff) scenario = 1;
		else scenario = 2;

		Ray newRay = Ray(o, ray.Direction);
		ignore = nullptr;

		if (scenario == 0) {
			lastSurface = MainObject->SurfaceIntersect(newRay);
		}
		else if (scenario == 1) {
			SurfaceIntersection mainT = MainObject->SurfaceIntersect(newRay);
			SurfaceIntersection diffT = SurfaceIntersectDifference(newRay, ignore);

			if (diffT.T < 0 || mainT.T < diffT.T) {
				mainT.T = tt + mainT.T;
				return mainT;
			}else {
				diffT.T = tt + diffT.T;
				diffT.Normal = diffT.Normal.Inverse();
				return diffT;
			}
		}
		else {
			lastSurface = SurfaceIntersectDifference(newRay, ignore);
		}

		if (lastSurface.T < 0) return SurfaceIntersection::NoIntersection();
		o = o + ray.Direction * (lastSurface.T * 1.000001);
		tt += lastSurface.T;
		prevScenario = scenario;
	}
}

bool SetDifferenceObject::Contains(Vec3f point) {
	return MainObject->Contains(point) && !ContainsDifference(point, nullptr);
}

double SetDifferenceObject::IntersectDifference(Ray& const ray, Object*& ignore) {
	double t = -1;

	for (int i = 0; i < Difference.size(); i++) {
		double tt = Difference[i]->Intersect(ray);
		if (tt < 0) continue;
		if (t < 0 || tt < t) t = tt;
		ignore = Difference[i];
	}

	return t;
}

SurfaceIntersection SetDifferenceObject::SurfaceIntersectDifference(Ray& const ray, Object*& ignore) {
	SurfaceIntersection output = SurfaceIntersection::NoIntersection();

	for (int i = 0; i < Difference.size(); i++) {
		Object* obj = Difference[i];

		SurfaceIntersection intersection = obj->SurfaceIntersect(ray);
		if (output.DoesIntersect() && (!intersection.DoesIntersect() || intersection.T > output.T)) continue;

		output = intersection;
		ignore = obj;
	}

	return output;
}

bool SetDifferenceObject::ContainsDifference(Vec3f point, Object* ignore) {
	for (int i = 0; i < Difference.size(); i++) {
		if (ignore != nullptr && Difference[i] == ignore) continue;
		if (Difference[i]->Contains(point)) return true;
	}

	return false;
}