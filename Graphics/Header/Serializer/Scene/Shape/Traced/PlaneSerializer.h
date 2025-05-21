#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Shape/Traced/Plane.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"
#include "../../../SerializerId.h"

class PlaneSerializer : public ItemSerializer<Object*>
{
public:
	PlaneSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<FlatSurface*>* flatSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_flatSurfaceSerializer = flatSurfaceSerializer;;
	}

	nlohmann::json Serialize(Object* item) override {
		Plane* plane = (Plane*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(plane->Origin);
		data["Normal"] = m_vec3fSerializer->Serialize(plane->Normal);
		data[SerializerId::Id[typeid(item)]] = m_flatSurfaceSerializer->Serialize(plane->Surface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Plane* plane = new Plane(m_vec3fSerializer->Deserialize(data["Location"]), m_vec3fSerializer->Deserialize(data["Normal"]).Normal());
		plane->Surface = m_flatSurfaceSerializer->Deserialize(data);

		return plane;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<FlatSurface*>* m_flatSurfaceSerializer;
};