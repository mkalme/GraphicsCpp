#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Sky/SkyBox.h"
#include "../../../Utilities/Reference.h"

class SkyBoxSerializer : public ItemSerializer<Sky*>
{
public:

	SkyBoxSerializer(ItemSerializer<Vec3f>* vec3fSerializer, Reference<std::string>* currentDirectory) {
		m_vec3fSerializer = vec3fSerializer;
		m_currentDirectory = currentDirectory;
	}

	nlohmann::json Serialize(Sky* item) override {
		SkyBox* skybox = (SkyBox*)item;

		nlohmann::json data;
		data["ImagePath"] = skybox->ImagePath;
		data["Offset"] = skybox->Offset;
		data["FogColor"] = m_vec3fSerializer->Serialize(skybox->FogColor);
		data["FogEnabled"] = skybox->FogEnabled;

		return data;
	}

	Sky* Deserialize(nlohmann::json data) override {
		std::string path = m_currentDirectory->Item;
		path = path.append("\\").append(data["ImagePath"]);

		SkyBox* sky = new SkyBox(new StbImageBuffer(path.c_str()), data["Offset"]);
		sky->ImagePath = data["ImagePath"];
		sky->FogColor = m_vec3fSerializer->Deserialize(data["FogColor"]);
		sky->FogEnabled = data["FogEnabled"];

		return sky;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	Reference<std::string>* m_currentDirectory;
};