#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Camera/ParallelCamera.h"

class ParallelCameraSerializer : public ItemSerializer<Camera*>
{
public:
	ParallelCameraSerializer(ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<Rotation>* rotationSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_rotationSerializer = rotationSerializer;
	}

	nlohmann::json Serialize(Camera* item) override {
		ParallelCamera* camera = (ParallelCamera*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(camera->Origin);
		data["Direction"] = m_vec3fSerializer->Serialize(camera->Direction);
		data["PlaneHorizontalLength"] = camera->PlaneHorizontalLength;
		data["RotationInPlane"] = m_rotationSerializer->Serialize(camera->RotationInPlane);

		return data;
	}

	Camera* Deserialize(nlohmann::json data) override {
		ParallelCamera* camera = new ParallelCamera();
		camera->Origin = m_vec3fSerializer->Deserialize(data["Location"]);
		camera->Direction = m_vec3fSerializer->Deserialize(data["Direction"]).Normal();
		camera->PlaneHorizontalLength = data["PlaneHorizontalLength"];

		if (data.contains("RotationInPlane")) {
			camera->RotationInPlane = m_rotationSerializer->Deserialize(data["RotationInPlane"]);
		}

		return camera;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	ItemSerializer<Rotation>* m_rotationSerializer;
};