#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Shape/Marched/MarchedCylinder.h"
#include "../../../../Scene/Surface/Uv/UvSurface.h"
#include "../../../SerializerId.h"

class MarchedCylinderSerializer : public ItemSerializer<Object*>
{
public:
	MarchedCylinderSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<UvSurface*>* uvSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_uvSurfaceSerializer = uvSurfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		MarchedCylinder* cylinder = (MarchedCylinder*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(cylinder->Location);
		data["Radius"] = cylinder->Radius;
		data[SerializerId::Id[typeid(item)]] = m_uvSurfaceSerializer->Serialize(cylinder->UvSurface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		MarchedCylinder* cylinder = new MarchedCylinder();

		cylinder->Location = m_vec3fSerializer->Deserialize(data["Location"]);
		cylinder->Radius = data["Radius"];
		cylinder->UvSurface = m_uvSurfaceSerializer->Deserialize(data);

		return cylinder;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<UvSurface*>* m_uvSurfaceSerializer;
};