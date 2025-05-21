#pragma once
#include "../Scene/Sky/Sky.h"
#include "../Scene/Sky/SolidColorSky.h"
#include "../Scene/Camera/Camera.h"
#include "../Scene/Light/Light.h"
#include "../Scene/Shape/Object.h"
#include <vector>
#include "Fog/Fog.h"

class Scene
{
public:
	Camera* CameraObj;

	Sky* Sky = new SolidColorSky(Vec3f(0));
	Fog* Fog;
	Vec3f AmbientLight;
	std::vector<Light*> LightSources;
	std::vector<Object*> Objects;

	Scene(Camera* camera);
	Scene();
};