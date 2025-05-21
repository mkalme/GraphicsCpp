#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Light/DirectionalLight.h"

class DirectionalLightSerializer : public ItemSerializer<Light*>
{
public:
	DirectionalLightSerializer(ItemSerializer<Vec3f>* vec3fSerializer) {
		m_vec3fSerializer = vec3fSerializer;
	}

	nlohmann::json Serialize(Light* item) override {
		DirectionalLight* light = (DirectionalLight*)item;

		nlohmann::json data;
		data["DirectionInSky"] = m_vec3fSerializer->Serialize(light->DirectionInSky);
		data["Lumens"] = light->Lumens;
		data["Color"] = m_vec3fSerializer->Serialize(light->Color);

		return data;
	}

	Light* Deserialize(nlohmann::json data) override {
		DirectionalLight* light = new DirectionalLight();

		light->DirectionInSky = m_vec3fSerializer->Deserialize(data["DirectionInSky"]).Normal();
		light->Lumens = data["Lumens"];
		light->Color = m_vec3fSerializer->Deserialize(data["Color"]);

		return light;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
};