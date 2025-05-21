#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Shape/Traced/Pyramid.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"
#include "../../../../Scene/Shape/Object.h"

class PyramidSerializer : public ItemSerializer<Object*>
{
public:
	PyramidSerializer(ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<SurfaceResult>* surfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_surfaceSerializer = surfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		Pyramid* pyramid = (Pyramid*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(pyramid->Location);
		data["Radius"] = pyramid->Radius;
		data["Sides"] = pyramid->Sides;
		data["Height"] = pyramid->Height;
		data["Surface"] = m_surfaceSerializer->Serialize(pyramid->GetSurface());

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Pyramid* pyramid = new Pyramid(m_vec3fSerializer->Deserialize(data["Location"]), data["Height"], data["Radius"], data["Sides"]);
		pyramid->SetSurface(m_surfaceSerializer->Deserialize(data["Surface"]));

		return pyramid;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	ItemSerializer<SurfaceResult>* m_surfaceSerializer;
};