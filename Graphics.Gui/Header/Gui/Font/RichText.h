#pragma once
#include "RichFontSegment.h"
#include <vector>

class RichText
{
public:
	std::vector<RichFontSegment> Segments = std::vector<RichFontSegment>();

	int LineSpacing = 1;
	int CharacterSpacing = 1;
	int Scale = 2;

	RichText& Add(RichFontSegment segment);
	RichText& AddLine(RichFontSegment segment);
};

