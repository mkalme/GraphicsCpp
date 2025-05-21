#define STB_IMAGE_IMPLEMENTATION
#include "../../../Header/External/stb_image.h"
#include "../../../Header/Utilities/ImageBuffer/StbImageBuffer.h"

StbImageBuffer::StbImageBuffer(int width, int height, unsigned char* pixelData) : GlfwImageBuffer(width, height, pixelData) {}
StbImageBuffer::StbImageBuffer(const char* imagePath) : GlfwImageBuffer(0, 0, 0) {
	m_pixelData = stbi_load(imagePath, &m_width, &m_height, NULL, 4);
}

int StbImageBuffer::GetIndex(int x, int y) {
	return (y * m_width + x) * 4;
}