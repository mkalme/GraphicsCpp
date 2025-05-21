#pragma once
#include "../../../ItemSerializer.h"
#include "../../../KeyedItemSerializer.h"
#include "../../../../Scene/Shape/Set/SetDifferenceObject.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Shape/Object.h"
#include "../../../SerializerId.h"

class SetDifferenceObjectSerializer : public ItemSerializer<Object*>
{
public:
	SetDifferenceObjectSerializer(KeyedItemSerializer<Object*>* objectSerializer) {
		m_objectSerializer = objectSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		SetDifferenceObject* set = (SetDifferenceObject*)item;

		nlohmann::json data;
		
		Object* mainObj = set->MainObject;
		nlohmann::json mainObjectData;
		std::string mainObjectKey = SerializerId::Id[typeid(mainObj)];
		mainObjectData[mainObjectKey] = m_objectSerializer->Serialize(mainObj);
		data["MainObject"] = mainObjectData;

		nlohmann::json differenceObjects = nlohmann::json::array();
		for (int i = 0; i < set->Difference.size(); i++) {
			Object* object = set->Difference[i];

			nlohmann::json differenceObjectData;
			std::string differenceObjectKey = SerializerId::Id[typeid(object)];
			differenceObjectData[differenceObjectKey] = m_objectSerializer->Serialize(object);

			differenceObjects.push_back(differenceObjectData);
		}
		data["Difference"] = differenceObjects;

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		Object* mainObject = m_objectSerializer->Deserialize(data["MainObject"]);
		std::vector<Object*> difference = std::vector<Object*>();

		nlohmann::json differenceObjectData = data["Difference"];
		for (auto it = differenceObjectData.begin(); it != differenceObjectData.end(); ++it) {
			difference.push_back(m_objectSerializer->Deserialize(*it));
		}

		return new SetDifferenceObject(mainObject, difference);
	}
private:
	KeyedItemSerializer<Object*>* m_objectSerializer;
};