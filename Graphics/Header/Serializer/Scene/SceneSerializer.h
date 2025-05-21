#pragma once
#include "../ItemSerializer.h"
#include "../Math/Vec3fSerializer.h"
#include "../../Scene/Scene.h"
#include "../SerializerCatalog.h"

class SceneSerializer : public ItemSerializer<Scene*>
{
public:
	SceneSerializer(SerializerCatalog* catalog) {
		m_catalog = catalog;
	}

	nlohmann::json Serialize(Scene* item) override {
		nlohmann::json data;

		std::string cameraKey = SerializerId::Id[typeid(item->CameraObj)];
		data[cameraKey] = (*m_catalog->CameraMap)[cameraKey]->Serialize(item->CameraObj);

		std::string fogKey = SerializerId::Id[typeid(item->Fog)];
		data[fogKey] = (*m_catalog->FogMap)[fogKey]->Serialize(item->Fog);

		std::string skyKey = SerializerId::Id[typeid(item->Sky)];
		data[skyKey] = (*m_catalog->SkyMap)[skyKey]->Serialize(item->Sky);

		nlohmann::json objects = nlohmann::json::array();
		for (int i = 0; i < item->Objects.size(); i++) {
			Object* object = item->Objects[i];

			nlohmann::json objectData;
			std::string objectKey = SerializerId::Id[typeid(object)];
			objectData[objectKey] = m_catalog->Objects->Serialize(object);

			objects.push_back(objectData);
		}
		data["Objects"] = objects;

		nlohmann::json lightSources = nlohmann::json::array();
		for (int i = 0; i < item->LightSources.size(); i++) {
			Light* light = item->LightSources[i];

			nlohmann::json lightData;
			std::string lightKey = SerializerId::Id[typeid(light)];
			lightData[lightKey] = (*m_catalog->LightMap)[lightKey]->Serialize(light);

			lightSources.push_back(lightData);
		}
		data["Lights"] = lightSources;

		data["AmbientLight"] = m_catalog->Vec3f->Serialize(item->AmbientLight);

		return data;
	}

	Scene* Deserialize(nlohmann::json data) override {
		Scene* scene = new Scene();
		scene->CameraObj = m_catalog->Cameras->Deserialize(data);

		nlohmann::json objectData = data["Objects"];
		for (auto it = objectData.begin(); it != objectData.end(); ++it) {
			scene->Objects.push_back(m_catalog->Objects->Deserialize(*it));
		}

		nlohmann::json lightData = data["Lights"];
		for (auto it = lightData.begin(); it != lightData.end(); ++it) {
			scene->LightSources.push_back(m_catalog->Lights->Deserialize(*it));
		}

		scene->Fog = m_catalog->Fogs->Deserialize(data);
		scene->Sky = m_catalog->Skies->Deserialize(data);
		scene->AmbientLight = m_catalog->Vec3f->Deserialize(data["AmbientLight"]);

		return scene;
	}
private:
	SerializerCatalog* m_catalog;
};