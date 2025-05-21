#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Shape/Traced/FlatPolygon.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"
#include "../../../SerializerId.h"

class FlatPolygonSerializer : public ItemSerializer<Object*>
{
public:
	FlatPolygonSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<FlatSurface*>* flatSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_flatSurfaceSerializer = flatSurfaceSerializer;;
	}

	nlohmann::json Serialize(Object* item) override {
		FlatPolygon* plane = (FlatPolygon*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(plane->Location);
		data["Radius"] = plane->Radius;
		data["Sides"] = plane->Sides;
		data[SerializerId::Id[typeid(item)]] = m_flatSurfaceSerializer->Serialize(plane->Surface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		FlatPolygon* plane = new FlatPolygon(m_vec3fSerializer->Deserialize(data["Location"]), data["Radius"], data["Sides"]);
		plane->Surface = m_flatSurfaceSerializer->Deserialize(data);

		return plane;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<FlatSurface*>* m_flatSurfaceSerializer;
};