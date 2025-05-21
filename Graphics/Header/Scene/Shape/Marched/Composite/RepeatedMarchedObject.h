#pragma once
#include "../MarchedObject.h"
#include "../../../../Math/Vec2f.h"

class RepeatedMarchedObject : public MarchedObject
{
public:
	Vec2f Corner1;
	Vec2f Corner2;

	int MaxXCells = 10;
	int MinXCells = -10;
	int MaxZCells = 10;
	int MinZCells = -10;

	MarchedObject* Object;

	double GetDistance(Ray& const ray) override;
	void GetNormalAndSurface(Vec3f point, Vec3f &normal, SurfaceResult &surface) override;
	bool Contains(Vec3f point) override;
private:
	Vec3f ModPoint(Vec3f point);
	double DoMod(double value, double offset, double width, double maxN, double minN);
};

