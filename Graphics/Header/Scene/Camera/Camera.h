#pragma once
#include "../../Renderer/ThreadInfo.h"
#include "../../Math/Vec3f.h"
#include "../../Math/Ray.h"
#include "../../Math/Rotation.h"

class Camera
{
public:
	Vec3f Origin;
	Vec3f Direction;
	Rotation RotationInPlane = Rotation(0);

	virtual void SetDimensions(int height, int width);
	virtual Ray* GenerateRays(ThreadInfo info);
};
