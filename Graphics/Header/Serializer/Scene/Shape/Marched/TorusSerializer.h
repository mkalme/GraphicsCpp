#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Shape/Marched/Torus.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"
#include "../../../SerializerId.h"
#include "../../../KeyedItemSerializer.h"

class TorusSerializer : public ItemSerializer<Object*>
{
public:
	TorusSerializer(ItemSerializer<Vec3f>* vec3fSerializer, KeyedItemSerializer<UvSurface*>* uvSurfaceSerializer) {
		m_vec3fSerializer = vec3fSerializer;
		m_uvSurfaceSerializer = uvSurfaceSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		Torus* torus = (Torus*)item;

		nlohmann::json data;
		data["Location"] = m_vec3fSerializer->Serialize(torus->Location);
		data["Radius1"] = torus->Radius1;
		data["Radius2"] = torus->Radius2;
		data[SerializerId::Id[typeid(item)]] = m_uvSurfaceSerializer->Serialize(torus->UvSurface);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Torus* torus = new Torus();
		
		torus->Location = m_vec3fSerializer->Deserialize(data["Location"]);
		torus->Radius1 = data["Radius1"];
		torus->Radius2 = data["Radius2"];
		torus->UvSurface = m_uvSurfaceSerializer->Deserialize(data);

		return torus;
	}
private:
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	KeyedItemSerializer<UvSurface*>* m_uvSurfaceSerializer;
};