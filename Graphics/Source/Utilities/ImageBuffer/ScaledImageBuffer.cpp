#include "../../../Header/Utilities/ImageBuffer/ScaledImageBuffer.h"

ScaledImageBuffer::ScaledImageBuffer(ImageBuffer* buffer, int scale) {
	m_buffer = buffer;
	m_scale = scale;
}

void ScaledImageBuffer::SetPixel(int x, int y, Vec3f pixel) {
	for (int yi = 0; yi < m_scale; yi++) {
		for (int xi = 0; xi < m_scale; xi++) {
			int xp = x * m_scale + xi;
			int yp = y * m_scale + yi;
			if (xp >= m_buffer->GetWidth() || yp >= m_buffer->GetHeight()) continue;

			m_buffer->SetPixel(xp, yp, pixel);
		}
	}
}

int ScaledImageBuffer::GetWidth() {
	return ceil(m_buffer->GetWidth() / (double)m_scale);
}

int ScaledImageBuffer::GetHeight() {
	return ceil(m_buffer->GetHeight() / (double)m_scale);
}