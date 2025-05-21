#include "../../Header/Scene/Scene.h"

Scene::Scene() = default;
Scene::Scene(Camera* camera) {
	CameraObj = camera;

	Objects = std::vector<Object*>();
	LightSources = std::vector<Light*>();
	AmbientLight = Vec3f(0);
}