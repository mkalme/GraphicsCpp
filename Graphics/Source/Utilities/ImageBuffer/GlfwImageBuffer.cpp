#include "../../../Header/Utilities/ImageBuffer/GlfwImageBuffer.h"

GlfwImageBuffer::GlfwImageBuffer(int width, int height, unsigned char* pixelData) {
	m_width = width;
	m_height = height;
	m_pixelData = pixelData;
}

int GlfwImageBuffer::GetWidth() {
	return m_width;
}
int GlfwImageBuffer::GetHeight() {
	return m_height;
}

Vec3f GlfwImageBuffer::GetPixel(int x, int y) {
	if (!IsWithinBounds(x, y)) return Vec3f(0);

	int index = GetIndex(x, y);
	return ReadIndexedPixel(index);
}
void GlfwImageBuffer::SetPixel(int x, int y, Vec3f pixel) {
	if (!IsWithinBounds(x, y)) return;

	int index = GetIndex(x, y);
	WriteIndexedPixel(index, pixel);
}

int GlfwImageBuffer::IsWithinBounds(int x, int y) {
	return x > -1 && y > -1 && x < m_width && y < m_width;
}

Vec3f GlfwImageBuffer::ReadIndexedPixel(int index) {
	return Vec3f(m_pixelData[index] / 255.0, m_pixelData[index + 1] / 255.0, m_pixelData[index + 2] / 255.0);
}

void GlfwImageBuffer::WriteIndexedPixel(int index, Vec3f pixel) {
	m_pixelData[index] = (unsigned char)(pixel.X * 255);
	m_pixelData[index + 1] = (unsigned char)(pixel.Y * 255);
	m_pixelData[index + 2] = (unsigned char)(pixel.Z * 255);
	m_pixelData[index + 3] = 255;
}

int GlfwImageBuffer::GetIndex(int x, int y) {
	return ((m_height - y - 1) * m_width + x) * m_bytesPerPixel;
}