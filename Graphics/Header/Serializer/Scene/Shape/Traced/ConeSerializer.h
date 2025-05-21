#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../SerializerId.h"
#include "../../../../Scene/Shape/Traced/Cone.h"

class ConeSerializer : public ItemSerializer<Object*>
{
public:
	ConeSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<UvSurface*>* uvSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_uvSurfaceSerializer = uvSurfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		Cone* cone = (Cone*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(cone->Location);
		data["Radius"] = cone->Radius;
		data["Height"] = cone->Height;
		data[SerializerId::Id[typeid(item)]] = m_uvSurfaceSerializer->Serialize(cone->UvSurface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Cone* cone = new Cone();

		cone->Location = m_vec3fSerializer->Deserialize(data["Location"]);
		cone->Radius = data["Radius"];
		cone->Height = data["Height"];
		cone->UvSurface = m_uvSurfaceSerializer->Deserialize(data);

		return cone;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<UvSurface*>* m_uvSurfaceSerializer;
};