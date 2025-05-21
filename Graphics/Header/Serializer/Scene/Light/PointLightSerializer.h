#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Light/PointLight.h"

class PointLightSerializer : public ItemSerializer<Light*>
{
public:
	PointLightSerializer(ItemSerializer<Vec3f>* vec3fSerializer) {
		m_vec3fSerializer = vec3fSerializer;
	}

	nlohmann::json Serialize(Light* item) override {
		PointLight* light = (PointLight*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(light->Location);
		data["Lumens"] = light->Lumens;
		data["Color"] = m_vec3fSerializer->Serialize(light->Color);

		return data;
	}

	Light* Deserialize(nlohmann::json data) override {
		PointLight* light = new PointLight();

		light->Location = m_vec3fSerializer->Deserialize(data["Location"]);
		light->Lumens = data["Lumens"];
		light->Color = m_vec3fSerializer->Deserialize(data["Color"]);

		return light;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
};