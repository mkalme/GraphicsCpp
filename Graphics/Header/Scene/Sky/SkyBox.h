#pragma once
#include "Sky.h"
#include "../../Utilities/ImageBuffer/ImageBuffer.h"
#include "../../Math/Vec3f.h"
#include <string>

class SkyBox : public Sky
{
public:
	ImageBuffer* Buffer;
	double Offset;

	Vec3f FogColor;
	bool FogEnabled = false;

	std::string ImagePath;

	SkyBox();
	SkyBox(ImageBuffer* buffer, double offset);

	Vec3f GetColor(Vec3f direction) override;
private:
	void GetUv(Vec3f n, double& u, double& v);
};

