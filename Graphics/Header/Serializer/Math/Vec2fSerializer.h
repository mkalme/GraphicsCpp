#pragma once
#include "../ItemSerializer.h"
#include "../../Math/Vec2f.h"

class Vec2fSerializer : public ItemSerializer<Vec2f>
{
public:
	nlohmann::json Serialize(Vec2f item) {
		return nlohmann::json::array({ item.X, item.Y });
	}

	Vec2f Deserialize(nlohmann::json data) {
		return Vec2f(data[0], data[1]);
	}
};