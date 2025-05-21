#pragma once
#include "Camera.h"
#include "../../Math/Rotation.h"
#include <climits>

class PerspectiveCamera : public Camera
{
public:
	double FocalLength;

	PerspectiveCamera();
	PerspectiveCamera(Vec3f origin, Vec3f direction, double focalLength);

	void SetDimensions(int height, int width) override;
	Ray* GenerateRays(ThreadInfo info) override;
private:
	Ray* m_rayBuffer = nullptr;
	int m_prevWidth = INT_MIN;
	int m_prevHeight = INT_MIN;
	Rotation m_hRotation;
	Rotation m_vRotation;

	void AllocateBuffer(int width, int height);
};

