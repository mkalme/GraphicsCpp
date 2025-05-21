#pragma once
#include "ImageBuffer.h"

class GlfwImageBuffer : public ImageBuffer
{
public:
	GlfwImageBuffer(int width, int height, unsigned char* pixelData);

	int GetWidth() override;
	int GetHeight() override;

	Vec3f GetPixel(int x, int y) override;
	void SetPixel(int x, int y, Vec3f pixel) override;
protected:
	int m_width;
	int m_height;
	unsigned char* m_pixelData;
	int m_bytesPerPixel = 4;

	virtual int IsWithinBounds(int x, int y);
	virtual Vec3f ReadIndexedPixel(int index);
	virtual void WriteIndexedPixel(int index, Vec3f pixel);
	virtual int GetIndex(int x, int y);
};

