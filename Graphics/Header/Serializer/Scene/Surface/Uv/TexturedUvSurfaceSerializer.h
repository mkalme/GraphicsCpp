#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Surface/Uv/TexturedUvSurface.h"
#include "../../../../../Header/Utilities/ImageBuffer/StbImageBuffer.h"

class TexturedUvSurfaceSerializer : public ItemSerializer<UvSurface*>
{
public:
	TexturedUvSurfaceSerializer(ItemSerializer<SurfaceResult>* surfaceResultSerializer, Reference<std::string>* currentDirectory) {
		m_surfaceResultSerializer = surfaceResultSerializer;
		m_currentDirectory = currentDirectory;
	}

	nlohmann::json Serialize(UvSurface* item) override {
		TexturedUvSurface* surface = (TexturedUvSurface*)item;

		nlohmann::json data;
		data["ImagePath"] = surface->ImagePath;
		data["Offset"] = surface->Offset;
		data["DefaultSurface"] = m_surfaceResultSerializer->Serialize(surface->DefaultSurface);

		return data;
	}

	UvSurface* Deserialize(nlohmann::json data) override {
		std::string path = m_currentDirectory->Item;
		path = path.append("\\").append(data["ImagePath"]);

		TexturedUvSurface* surface = new TexturedUvSurface();
		surface->Buffer = new StbImageBuffer(path.c_str());
		surface->ImagePath = data["ImagePath"];
		surface->Offset = data["Offset"];
		surface->DefaultSurface = m_surfaceResultSerializer->Deserialize(data["DefaultSurface"]);

		return surface;
	}
private:
	ItemSerializer<SurfaceResult>* m_surfaceResultSerializer;
	Reference<std::string>* m_currentDirectory;
};