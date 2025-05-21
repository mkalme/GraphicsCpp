#pragma once
#include "../../Math/Vec3f.h"

class ImageBuffer
{
public:
	virtual int GetWidth();
	virtual int GetHeight();

	virtual Vec3f GetPixel(int x, int y);
	virtual void SetPixel(int x, int y, Vec3f pixel);
};