#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Shape/Traced/Cylinder.h"
#include "../../../../Scene/Surface/Uv/UvSurface.h"
#include "../../../SerializerId.h"

class CylinderSerializer : public ItemSerializer<Object*>
{
public:
	CylinderSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<UvSurface*>* uvSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_uvSurfaceSerializer = uvSurfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		Cylinder* cylinder = (Cylinder*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(cylinder->Location);
		data["Radius"] = cylinder->Radius;
		data[SerializerId::Id[typeid(item)]] = m_uvSurfaceSerializer->Serialize(cylinder->Surface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Cylinder* cylinder = new Cylinder();

		cylinder->Location = m_vec3fSerializer->Deserialize(data["Location"]);
		cylinder->Radius = data["Radius"];
		cylinder->Surface = m_uvSurfaceSerializer->Deserialize(data);

		return cylinder;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<UvSurface*>* m_uvSurfaceSerializer;
};