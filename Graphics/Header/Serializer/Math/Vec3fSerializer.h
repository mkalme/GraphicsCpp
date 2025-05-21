#pragma once
#include "../ItemSerializer.h"
#include "../../Math/Vec3f.h"

class Vec3fSerializer : public ItemSerializer<Vec3f>
{
public:
	nlohmann::json Serialize(Vec3f item) override {
		return nlohmann::json::array({ item.X, item.Y, item.Z });
	}

	Vec3f Deserialize(nlohmann::json data) {
		if (data.type() == nlohmann::json::value_t::string) {
			std::string hexString = std::string(data);
			if (hexString[0] == '#') hexString = hexString.erase(0, 1);

			int hex = strtol(hexString.c_str(), NULL, 16);

			double x = (double)((hex >> (8 * 2)) & 0xff) / 255.0;
			double y = (double)((hex >> (8 * 1)) & 0xff) / 255.0;
			double z = (double)((hex >> (8 * 0)) & 0xff) / 255.0;

			return Vec3f(x, y, z);
		}

		return Vec3f(data[0], data[1], data[2]);
	}
};

