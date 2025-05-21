#pragma once
#include "../ItemSerializer.h"
#include "../../Math/Rotation.h"

class RotationSerializer : public ItemSerializer<Rotation>
{
public:
	nlohmann::json Serialize(Rotation item) {
		return item.Radians / Rotation::PI() * 180.0;
	}

	Rotation Deserialize(nlohmann::json data) {
		return Rotation::FromDegrees(data);
	}
};