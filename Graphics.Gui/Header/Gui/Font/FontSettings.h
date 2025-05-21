#pragma once
#include "../Header/Math/Vec3f.h"

struct FontSettings
{
	Vec3f Foreground = Vec3f(255, 232, 61) / 255.0;
	Vec3f Background = Vec3f::Empty();
	int Scale = 3;
	int LineSpacing = 1;
	int CharacterSpacing = 1;
};