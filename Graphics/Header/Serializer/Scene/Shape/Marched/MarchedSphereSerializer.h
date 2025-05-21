#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../SerializerId.h"
#include "../../../../Scene/Shape/Marched/MarchedSphere.h"

class MarchedSphereSerializer : public ItemSerializer<Object*>
{
public:
	MarchedSphereSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<UvSurface*>* uvSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_uvSurfaceSerializer = uvSurfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		MarchedSphere* sphere = (MarchedSphere*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(sphere->Location);
		data["Radius"] = sphere->Radius;
		data[SerializerId::Id[typeid(item)]] = m_uvSurfaceSerializer->Serialize(sphere->UvSurface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		MarchedSphere* sphere = new MarchedSphere();

		sphere->Location = m_vec3fSerializer->Deserialize(data["Location"]);
		sphere->Radius = data["Radius"];
		sphere->UvSurface = m_uvSurfaceSerializer->Deserialize(data);

		return sphere;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<UvSurface*>* m_uvSurfaceSerializer;
};