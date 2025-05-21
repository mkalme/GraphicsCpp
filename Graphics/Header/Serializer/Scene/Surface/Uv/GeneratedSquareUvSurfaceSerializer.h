#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Surface/Uv/SolidUvSurface.h"

class GeneratedSquareUvSurfaceSerializer : public ItemSerializer<UvSurface*>
{
public:
	GeneratedSquareUvSurfaceSerializer(ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<SurfaceResult>* surfaceResultSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_surfaceResultSerializer = surfaceResultSerializer;
	}

	nlohmann::json Serialize(UvSurface* item) override {
		GeneratedSquareUvSurface* surface = (GeneratedSquareUvSurface*)item;

		nlohmann::json data;
		data["FirstColor"] = m_vec3fSerializer->Serialize(surface->FirstColor);
		data["SecondColor"] = m_vec3fSerializer->Serialize(surface->SecondColor);
		data["DefaultSurface"] = m_surfaceResultSerializer->Serialize(surface->DefaultSurface);
		data["SquareSizeU"] = surface->SquareSize_U;
		data["SquareSizeV"] = surface->SquareSize_V;

		return data;
	}

	UvSurface* Deserialize(nlohmann::json data) override {
		GeneratedSquareUvSurface* surface = new GeneratedSquareUvSurface();
		surface->FirstColor = m_vec3fSerializer->Deserialize(data["FirstColor"]);
		surface->SecondColor = m_vec3fSerializer->Deserialize(data["SecondColor"]);
		surface->DefaultSurface = m_surfaceResultSerializer->Deserialize(data["DefaultSurface"]);
		surface->SquareSize_U = data["SquareSizeU"];
		surface->SquareSize_V = data["SquareSizeV"];

		return surface;
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
	ItemSerializer<Vec3f>* m_vec3fSerializer;
};