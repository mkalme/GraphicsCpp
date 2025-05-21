#pragma once
#include "GlfwImageBuffer.h"

class StbImageBuffer : public GlfwImageBuffer
{
public:
	StbImageBuffer(int width, int height, unsigned char* pixelData);
	StbImageBuffer(const char* filePath);
protected:
	int GetIndex(int x, int y) override;
};