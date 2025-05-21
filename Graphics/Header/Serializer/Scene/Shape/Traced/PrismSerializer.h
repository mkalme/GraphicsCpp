#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Shape/Traced/Prism.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Shape/Object.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"

class PrismSerializer : public ItemSerializer<Object*>
{
public:
	PrismSerializer(ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<SurfaceResult>* surfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_surfaceSerializer = surfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		Prism* prism = (Prism*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(prism->Location);
		data["Height"] = prism->Height;
		data["Radius"] = prism->Radius;
		data["Sides"] = prism->Sides;
		data["Surface"] = m_surfaceSerializer->Serialize(prism->GetSurface());

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Prism* prism = new Prism(m_vec3fSerializer->Deserialize(data["Location"]), data["Height"], data["Radius"], data["Sides"]);
		prism->SetSurface(m_surfaceSerializer->Deserialize(data["Surface"]));

		return prism;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	ItemSerializer<SurfaceResult>* m_surfaceSerializer;
};