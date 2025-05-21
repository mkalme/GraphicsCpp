#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Camera/PerspectiveCamera.h"

class PerspectiveCameraSerializer : public ItemSerializer<Camera*>
{
public:
	PerspectiveCameraSerializer(ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<Rotation>* rotationSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_rotationSerializer = rotationSerializer;
	}

	nlohmann::json Serialize(Camera* item) override {
		PerspectiveCamera* camera = (PerspectiveCamera*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(camera->Origin);
		data["Direction"] = m_vec3fSerializer->Serialize(camera->Direction);
		data["FocalLength"] = camera->FocalLength;
		data["RotationInPlane"] = m_rotationSerializer->Serialize(camera->RotationInPlane);

		return data;
	}

	Camera* Deserialize(nlohmann::json data) override {
		PerspectiveCamera* camera = new PerspectiveCamera();
		camera->Origin = m_vec3fSerializer->Deserialize(data["Location"]);
		camera->Direction = m_vec3fSerializer->Deserialize(data["Direction"]).Normal();
		camera->FocalLength = data["FocalLength"];

		if (data.contains("RotationInPlane")) {
			camera->RotationInPlane = m_rotationSerializer->Deserialize(data["RotationInPlane"]);
		}

		return camera;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	ItemSerializer<Rotation>* m_rotationSerializer;
};