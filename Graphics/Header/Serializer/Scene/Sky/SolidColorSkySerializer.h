#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Sky/SolidColorSky.h"

class SolidColorSkySerializer : public ItemSerializer<Sky*>
{
public:
	SolidColorSkySerializer(ItemSerializer<Vec3f>* vec3fSerializer) {
		m_vec3fSerializer = vec3fSerializer;
	}

	nlohmann::json Serialize(Sky* item) override {
		return m_vec3fSerializer->Serialize(((SolidColorSky*)item)->Color);
	}

	Sky* Deserialize(nlohmann::json data) override {
		return new SolidColorSky(m_vec3fSerializer->Deserialize(data));
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
};