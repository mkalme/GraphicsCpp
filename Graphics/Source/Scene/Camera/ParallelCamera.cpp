#include "../../../Header/Scene/Camera/ParallelCamera.h"
#include "../../../Header/Math/Rotation.h"
#include <cmath>
#include <iostream>

void ParallelCamera::SetDimensions(int width, int height) {
	AllocateBuffer(width, height);

	m_hRotation = Rotation(atan2(Direction.X, Direction.Z));
	m_vRotation = Rotation(atan2(Direction.Y, sqrt(Direction.X * Direction.X + Direction.Z * Direction.Z)));
}

Ray* ParallelCamera::GenerateRays(ThreadInfo info) {
	double dx = 1.0 / m_prevWidth;
	double yTop = m_prevHeight / (double)m_prevWidth / 2.0;

	int delta = (int)ceil(m_prevHeight / (double)info.ThreadCount);
	int y1 = delta * info.Index;
	int y2 = std::min(y1 + delta, m_prevHeight);

	for (int y = y1; y < y2; y++) {
		for (int x = 0; x < m_prevWidth; x++) {
			double xp = 0.5 - dx / 2 - dx * x;
			double yp = yTop - dx / 2 - dx * y;
			double zp = 1;

			RotationInPlane.Rotate(xp, yp);

			Vec3f origin = Vec3f(xp * PlaneHorizontalLength, yp * PlaneHorizontalLength, 0);
			
			double vx = origin.Z, vy = origin.Y;
			m_vRotation.Rotate(vx, vy);

			double hx = vx, hy = origin.X;
			m_hRotation.Rotate(hx, hy);

			origin.X = hy;
			origin.Y = vy;
			origin.Z = hx;

			m_rayBuffer[m_prevWidth * y + x].Origin = Origin + origin;
			m_rayBuffer[m_prevWidth * y + x].Direction = Direction;
		}
	}

	return m_rayBuffer;
}

void ParallelCamera::AllocateBuffer(int width, int height) {
	if (width == m_prevWidth && height == m_prevHeight) return;
	if (m_rayBuffer != nullptr) delete m_rayBuffer;

	m_prevWidth = width;
	m_prevHeight = height;

	m_rayBuffer = new Ray[width * height];
	for (int i = 0; i < width * height; i++) {
		m_rayBuffer[i] = Ray(Vec3f::Empty(), Vec3f::Empty());
	}
}