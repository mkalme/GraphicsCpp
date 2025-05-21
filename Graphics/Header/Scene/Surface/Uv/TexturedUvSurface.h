#pragma once
#include "UvSurface.h"
#include "../../../Utilities/ImageBuffer/ImageBuffer.h"
#include <string>

class TexturedUvSurface : public UvSurface
{
public:
	ImageBuffer* Buffer;
	double Offset;

	SurfaceResult DefaultSurface;

	std::string ImagePath;

	TexturedUvSurface();
	TexturedUvSurface(ImageBuffer* buffer, double offset, SurfaceResult defaultSurface);

	SurfaceResult GetSurface(double u, double v) override;
};

