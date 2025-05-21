#pragma once
#include <map>
#include <string>
#include <typeindex>
#include "../Scene/Camera/Camera.h"
#include "../Scene/Light/Light.h"
#include "../Scene/Sky/SolidColorSky.h"
#include "../Scene/Sky/SkyBox.h"
#include "../Scene/Surface/Flat/SolidFlatSurface.h"
#include "../Scene/Surface/Flat/RotatedFlatSurface.h"
#include "../Scene/Surface/Flat/CheckedFlatSurface.h"
#include "../Scene/Surface/Uv/SolidUvSurface.h"
#include "../Scene/Surface/Uv/GeneratedSquareUvSurface.h"
#include "../Scene/Surface/Uv/TexturedUvSurface.h"

class SerializerId
{
public:
	static std::map<std::type_index, std::string> Id;
};

