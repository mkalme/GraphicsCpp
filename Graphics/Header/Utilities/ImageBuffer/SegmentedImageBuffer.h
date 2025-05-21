#pragma once
#include "ImageBuffer.h"

class SegmentedImageBuffer : public ImageBuffer
{
public:
	SegmentedImageBuffer(ImageBuffer* buffer, int x, int y, int width, int height);

	int GetWidth() override;
	int GetHeight() override;

	Vec3f GetPixel(int x, int y) override;
	void SetPixel(int x, int y, Vec3f pixel) override;

	ImageBuffer* GetBuffer();
	int GetX();
	int GetY();
protected:
	ImageBuffer* m_buffer;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

