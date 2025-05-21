#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Surface/Flat/LineFlatSurface.h"

class LineFlatSurfaceSerializer : public ItemSerializer<FlatSurface*>
{
public:
	LineFlatSurfaceSerializer(ItemSerializer<SurfaceResult>* surfaceResultSerializer) {
		m_surfaceResultSerializer = surfaceResultSerializer;
	}

	nlohmann::json Serialize(FlatSurface* item) override {
		LineFlatSurface* surface = (LineFlatSurface*)item;

		nlohmann::json data;
		data["FirstSurface"] = m_surfaceResultSerializer->Serialize(surface->FirstSurfaceResult);
		data["SecondSurface"] = m_surfaceResultSerializer->Serialize(surface->SecondSurfaceResult);
		data["FirstLineWidth"] = surface->FirstLineWidth;
		data["SecondLineWidth"] = surface->SecondLineWidth;
		data["Offset"] = surface->Offset;

		return data;
	}

	FlatSurface* Deserialize(nlohmann::json data) override {
		LineFlatSurface* surface = new LineFlatSurface();

		surface->FirstSurfaceResult = m_surfaceResultSerializer->Deserialize(data["FirstSurface"]);
		surface->SecondSurfaceResult = m_surfaceResultSerializer->Deserialize(data["SecondSurface"]);
		surface->FirstLineWidth = data["FirstLineWidth"];
		surface->SecondLineWidth = data["SecondLineWidth"];
		surface->Offset = data["Offset"];

		return surface;
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
};