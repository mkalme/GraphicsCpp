#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Surface/Uv/CheckedUvSurface.h"

class CheckedUvSurfaceSerializer : public ItemSerializer<UvSurface*>
{
public:
	CheckedUvSurfaceSerializer(ItemSerializer<SurfaceResult>* surfaceResultSerializer) {
		m_surfaceResultSerializer = surfaceResultSerializer;
	}

	nlohmann::json Serialize(UvSurface* item) override {
		CheckedUvSurface* surface = (CheckedUvSurface*)item;

		nlohmann::json data;
		data["FirstCell"] = m_surfaceResultSerializer->Serialize(surface->FirstCell);
		data["SecondCell"] = m_surfaceResultSerializer->Serialize(surface->SecondCell);
		data["SquareSizeU"] = surface->SquareSize_U;
		data["SquareSizeV"] = surface->SquareSize_V;

		return data;
	}

	UvSurface* Deserialize(nlohmann::json data) override {
		CheckedUvSurface* surface = new CheckedUvSurface();
		surface->FirstCell = m_surfaceResultSerializer->Deserialize(data["FirstCell"]);
		surface->SecondCell = m_surfaceResultSerializer->Deserialize(data["SecondCell"]);
		surface->SquareSize_U = data["SquareSizeU"];
		surface->SquareSize_V = data["SquareSizeV"];

		return surface;
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
};