#pragma once
#include "../Header/Math/Vec3f.h"
#include <string>

struct RichFontSegment
{
	std::string Text;
	Vec3f Foreground;
	Vec3f Background;

	RichFontSegment(std::string text, Vec3f foreground, Vec3f background);
	RichFontSegment(std::string text, Vec3f foreground);
};

