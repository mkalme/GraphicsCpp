#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Shape/Traced/Box.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Shape/Object.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"

class BoxSerializer : public ItemSerializer<Object*>
{
public:
	BoxSerializer(ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<SurfaceResult>* surfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_surfaceSerializer = surfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		Box* box = (Box*)item;

		nlohmann::json data;
		data["FirstPoint"] = m_vec3fSerializer->Serialize(box->FirstPoint);
		data["SecondPoint"] = m_vec3fSerializer->Serialize(box->SecondPoint);
		data["Surface"] = m_surfaceSerializer->Serialize(box->GetSurface());

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Box* box = new Box(m_vec3fSerializer->Deserialize(data["FirstPoint"]), m_vec3fSerializer->Deserialize(data["SecondPoint"]));
		box->SetSurface(m_surfaceSerializer->Deserialize(data["Surface"]));

		return box;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	ItemSerializer<SurfaceResult>* m_surfaceSerializer;
};