#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Surface/Flat/CheckedFlatSurface.h"

class CheckedFlatSurfaceSerializer : public ItemSerializer<FlatSurface*>
{
public:
	CheckedFlatSurfaceSerializer(ItemSerializer<SurfaceResult>* surfaceResultSerializer) {
		m_surfaceResultSerializer = surfaceResultSerializer;
	}

	nlohmann::json Serialize(FlatSurface* item) override {
		CheckedFlatSurface* surface = (CheckedFlatSurface*)item;

		nlohmann::json data;
		data["Zoom"] = surface->Zoom;
		data["FirstCell"] = m_surfaceResultSerializer->Serialize(surface->FirstSurfaceResult);
		data["SecondCell"] = m_surfaceResultSerializer->Serialize(surface->SecondSurfaceResult);

		return data;
	}

	FlatSurface* Deserialize(nlohmann::json data) override {
		CheckedFlatSurface* surface = new CheckedFlatSurface();
		surface->Zoom = data["Zoom"];
		surface->FirstSurfaceResult = m_surfaceResultSerializer->Deserialize(data["FirstCell"]);
		surface->SecondSurfaceResult = m_surfaceResultSerializer->Deserialize(data["SecondCell"]);

		return surface;
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
};