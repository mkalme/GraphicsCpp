#pragma once
#include "../../../../ItemSerializer.h"
#include "../../../../../Scene/Shape/Marched/MarchedObject.h"
#include "../../../../../Scene/Shape/Marched/Composite/RepeatedMarchedObject.h"
#include "../../../../SerializerId.h"

class RepeatedMarchedObjectSerializer : public ItemSerializer<Object*>
{
public:
	RepeatedMarchedObjectSerializer(ItemSerializer<Vec2f>* vec2fSerializer, ItemSerializer<Object*>* objectSerializer) {
		m_vec2fSerializer = vec2fSerializer;
		m_objectSerializer = objectSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		RepeatedMarchedObject* object = (RepeatedMarchedObject*)item;

		nlohmann::json data;
		data["Corner1"] = m_vec2fSerializer->Serialize(object->Corner1);
		data["Corner2"] = m_vec2fSerializer->Serialize(object->Corner2);
		data["MaxXCells"] = object->MaxXCells;
		data["MinXCells"] = object->MinXCells;
		data["MaxZCells"] = object->MaxZCells;
		data["MinZCells"] = object->MinZCells;

		std::string objectKey = SerializerId::Id[typeid(object)];
		data[objectKey] = m_objectSerializer->Serialize(object);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		RepeatedMarchedObject* object = new RepeatedMarchedObject();

		object->Corner1 = m_vec2fSerializer->Deserialize(data["Corner1"]);
		object->Corner2 = m_vec2fSerializer->Deserialize(data["Corner2"]);
		object->MaxXCells = data["MaxXCells"];
		object->MinXCells = data["MinXCells"];
		object->MaxZCells = data["MaxZCells"];
		object->MinZCells = data["MinZCells"];
		object->Object = (MarchedObject*)m_objectSerializer->Deserialize(data);

		return object;
	}
private:
	ItemSerializer<Vec2f>* m_vec2fSerializer;
	ItemSerializer<Object*>* m_objectSerializer;
};