#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Shape/Set/UnionObject.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Shape/Object.h"
#include "../../../SerializerId.h"

class UnionObjectSerializer : public ItemSerializer<Object*>
{
public:
	UnionObjectSerializer(KeyedItemSerializer<Object*>* objectSerializer) {
		m_objectSerializer = objectSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		UnionObject* set = (UnionObject*)item;

		nlohmann::json data = nlohmann::json::array();
		for (int i = 0; i < set->Objects.size(); i++) {
			Object* object = set->Objects[i];

			nlohmann::json objectData;
			std::string objectKey = SerializerId::Id[typeid(object)];
			objectData[objectKey] = m_objectSerializer->Serialize(object);

			data.push_back(objectData);
		}

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		std::vector<Object*> objects = std::vector<Object*>();

		for (auto it = data.begin(); it != data.end(); ++it) {
			objects.push_back(m_objectSerializer->Deserialize(*it));
		}

		return new UnionObject(objects);
	}
private:
	KeyedItemSerializer<Object*>* m_objectSerializer;
};