#pragma once
#include "../../Math/Vec3f.h"

class Sky
{
public:
	virtual Vec3f GetColor(Vec3f direction);
};

