#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Surface/SurfaceResult.h"

class SurfaceResultSerializer : public ItemSerializer<SurfaceResult>
{
public:
	SurfaceResultSerializer(ItemSerializer<Vec3f>* vec3fSerializer) {
		m_vec3fSerializer = vec3fSerializer;
	}

	nlohmann::json Serialize(SurfaceResult item) override {
		nlohmann::json data;
		data["Color"] = m_vec3fSerializer->Serialize(item.Color);
		data["ReflectionIndex"] = item.ReflectionIndex;
		data["FresnelIndex"] = item.FresnelIndex;
		data["SpecularPow"] = item.SpecularPow;
		data["RefractionIndex"] = item.RefractionIndex;
		data["RefractionReflectionIndex"] = item.RefractionReflectionIndex;

		return data;
	}

	SurfaceResult Deserialize(nlohmann::json data) override {
		SurfaceResult result;

		result.Color = m_vec3fSerializer->Deserialize(data["Color"]);
		result.ReflectionIndex = data["ReflectionIndex"];
		result.FresnelIndex = data["FresnelIndex"];
		result.SpecularPow = data["SpecularPow"];
		result.RefractionIndex = data["RefractionIndex"];
		result.RefractionReflectionIndex = data["RefractionReflectionIndex"];

		return result;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
};