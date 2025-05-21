#pragma once
#include "../Math/Vec3f.h"

struct VignetteSettings {
public:
	bool Enabled = true;
	double Radius = 1.1;
	double Strength = 0.0015;
	Vec3f Color = Vec3f(0);
};

struct RenderSettings
{
public:
	int Scale = 2;
	int MaxDepth = 10;
	int MaxRefractionDepth = 5;
	int ThreadCount = 13;
	VignetteSettings Vignette = VignetteSettings();
};