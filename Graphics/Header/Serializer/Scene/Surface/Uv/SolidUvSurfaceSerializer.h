#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Surface/Uv/SolidUvSurface.h"

class SolidUvSurfaceSerializer : public ItemSerializer<UvSurface*>
{
public:
	SolidUvSurfaceSerializer(ItemSerializer<SurfaceResult>* surfaceResultSerializer) {
		m_surfaceResultSerializer = surfaceResultSerializer;
	}

	nlohmann::json Serialize(UvSurface* item) override {
		nlohmann::json data;
		data["Surface"] = m_surfaceResultSerializer->Serialize(((SolidUvSurface*)item)->Surface);

		return data;
	}

	UvSurface* Deserialize(nlohmann::json data) override {
		return new SolidUvSurface(m_surfaceResultSerializer->Deserialize(data["Surface"]));
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
};