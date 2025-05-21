#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Surface/Flat/RotatedFlatSurface.h"

class RotatedFlatSurfaceSerializer : public ItemSerializer<FlatSurface*>
{
public:
	RotatedFlatSurfaceSerializer(ItemSerializer<Rotation>* rotationSerializer, KeyedItemSerializer<FlatSurface*>* flatSurfaceSerializer) {
		m_rotationSerializer = rotationSerializer;
		m_flatSurfaceSerializer = flatSurfaceSerializer;
	}

	nlohmann::json Serialize(FlatSurface* item) override {
		RotatedFlatSurface* surface = (RotatedFlatSurface*)item;

		nlohmann::json data;
		data["Rotation"] = m_rotationSerializer->Serialize(surface->RotatedBy);
		data[SerializerId::Id[typeid(item)]] = m_flatSurfaceSerializer->Serialize(item);

		return data;
	}

	FlatSurface* Deserialize(nlohmann::json data) override {
		FlatSurface* wrapped = m_flatSurfaceSerializer->Deserialize(data);

		RotatedFlatSurface* surface = new RotatedFlatSurface(wrapped);
		surface->RotatedBy = m_rotationSerializer->Deserialize(data["Rotation"]);

		return surface;
	}
private:
	ItemSerializer<Rotation>* m_rotationSerializer;
	KeyedItemSerializer<FlatSurface*>* m_flatSurfaceSerializer;
};