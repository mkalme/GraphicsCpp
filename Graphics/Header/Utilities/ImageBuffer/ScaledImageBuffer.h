#pragma once
#include "ImageBuffer.h"

class ScaledImageBuffer : public ImageBuffer
{
public:
	ScaledImageBuffer(ImageBuffer* buffer, int scale);

	void SetPixel(int x, int y, Vec3f pixel) override;
	int GetWidth() override;
	int GetHeight() override;

	ImageBuffer GetBuffer();
	int GetScale();
protected:
	ImageBuffer* m_buffer;
	int m_scale;
};

