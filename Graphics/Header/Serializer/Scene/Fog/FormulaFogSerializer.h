#pragma once
#include "../../ItemSerializer.h"
#include "../../Math/Vec3fSerializer.h"
#include "../../../Scene/Fog/Formula/FormulaFog.h"

class FormulaFogSerializer : public ItemSerializer<Fog*>
{
public:
	FormulaFogSerializer(ItemSerializer<Vec3f>* vec3fSerializer) {
		m_vec3fSerializer = vec3fSerializer;
	}

	nlohmann::json Serialize(Fog* item) override {
		FormulaFog* fog = (FormulaFog*)item;

		nlohmann::json data;
		data["Enabled"] = fog->Enabled;
		data["Color"] = m_vec3fSerializer->Serialize(fog->Color);
		data["MinimumDistanceToEnable"] = fog->MinimumDistanceToEnable;

		nlohmann::json settings;
		settings["Formula"] = fog->GetFormula();
		settings["MinimumFogIntensity"] = fog->MinFogIntensity;
		settings["MaximumFogIntensity"] = fog->MaxFogIntensity;

		data["SettingsIfEnabled"] = settings;

		return data;
	}

	Fog* Deserialize(nlohmann::json data) override {
		nlohmann::json settings = data["SettingsIfEnabled"];
		
		FormulaFog* fog = new FormulaFog(settings["Formula"]);
		fog->Enabled = data["Enabled"];
		fog->Color = m_vec3fSerializer->Deserialize(data["Color"]);
		fog->MinimumDistanceToEnable = data["MinimumDistanceToEnable"];
		fog->MinFogIntensity = settings["MinimumFogIntensity"];
		fog->MaxFogIntensity = settings["MaximumFogIntensity"];

		return fog;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
};