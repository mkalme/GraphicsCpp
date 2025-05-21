#include "../../../Header/Utilities/ImageBuffer/SegmentedImageBuffer.h"

SegmentedImageBuffer::SegmentedImageBuffer(ImageBuffer* buffer, int x, int y, int width, int height) {
	m_buffer = buffer;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

int SegmentedImageBuffer::GetWidth() {
	return m_width;
}
int SegmentedImageBuffer::GetHeight() {
	return m_height;
}

Vec3f SegmentedImageBuffer::GetPixel(int x, int y) {
	return m_buffer->GetPixel(x + m_x, y + m_y);
}
void SegmentedImageBuffer::SetPixel(int x, int y, Vec3f pixel) {
	m_buffer->SetPixel(x + m_x, y + m_y, pixel);
}

ImageBuffer* SegmentedImageBuffer::GetBuffer() {
	return m_buffer;
}
int SegmentedImageBuffer::GetX() {
	return m_x;
}
int SegmentedImageBuffer::GetY() {
	return m_y;
}