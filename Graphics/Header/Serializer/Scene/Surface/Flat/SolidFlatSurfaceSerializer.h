#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Surface/Flat/SolidFlatSurface.h"

class SolidFlatSurfaceSerializer : public ItemSerializer<FlatSurface*>
{
public:
	SolidFlatSurfaceSerializer(ItemSerializer<SurfaceResult>* surfaceResultSerializer) {
		m_surfaceResultSerializer = surfaceResultSerializer;
	}

	nlohmann::json Serialize(FlatSurface* item) override {
		nlohmann::json data;
		data["Surface"] = m_surfaceResultSerializer->Serialize(((SolidFlatSurface*)item)->Surface);

		return data;
	}

	FlatSurface* Deserialize(nlohmann::json data) override {
		return new SolidFlatSurface(m_surfaceResultSerializer->Deserialize(data["Surface"]));
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
};