#pragma once
#include "../../../ItemSerializer.h"
#include "../../../../Scene/Shape/Composite/TransformableObject.h"
#include "../../../../Math/Vec3f.h"
#include "../../../../Scene/Shape/Object.h"
#include "../../../../Scene/Surface/Flat/FlatSurface.h"
#include "../../../../Math/Rotation.h"
#include "../../../SerializerId.h"

class TransformableObjectSerializer : public ItemSerializer<Object*>
{
public:
	TransformableObjectSerializer(ItemSerializer<Vec2f>* vec2fSerializer, ItemSerializer<Vec3f>* vec3fSerializer, ItemSerializer<Rotation>* rotationSerializer, ItemSerializer<Object*>* objectSerializer) {
		m_vec2fSerializer = vec2fSerializer;
		m_vec3fSerializer = vec3fSerializer;
		m_rotationSerializer = rotationSerializer;
		m_objectSerializer = objectSerializer;
	}

	nlohmann::json Serialize(Object* item) override {
		TransformableObject* object = (TransformableObject*)item;

		nlohmann::json data;
		data["RotationalPoint"] = m_vec3fSerializer->Serialize(object->RotationalPoint);
		data["VerticalAxis"] = m_vec2fSerializer->Serialize(object->GetVerticalAxis());
		data["HorizontalRotation"] = m_rotationSerializer->Serialize(object->GetHorizontalRotation());
		data["VerticalRotation"] = m_rotationSerializer->Serialize(object->GetVerticalRotation());
		data["Offset"] = m_vec3fSerializer->Serialize(object->Offset);

		std::string objectKey = SerializerId::Id[typeid(object)];
		data[objectKey] = m_objectSerializer->Serialize(object);

		return data;
	}

	Object* Deserialize(nlohmann::json data) override {
		TransformableObject* object = new TransformableObject();

		object->RotationalPoint = m_vec3fSerializer->Deserialize(data["RotationalPoint"]);
		object->SetVerticalAxis(m_vec2fSerializer->Deserialize(data["VerticalAxis"]).Normal());
		object->SetHorizontalRotation(m_rotationSerializer->Deserialize(data["HorizontalRotation"]));
		object->SetVerticalRotation(m_rotationSerializer->Deserialize(data["VerticalRotation"]));
		object->Offset = m_vec3fSerializer->Deserialize(data["Offset"]);
		object->Object = m_objectSerializer->Deserialize(data);

		return object;
	}
private:
	ItemSerializer<Vec2f>* m_vec2fSerializer;
	ItemSerializer<Vec3f>* m_vec3fSerializer;
	ItemSerializer<Rotation>* m_rotationSerializer;
	ItemSerializer<Object*>* m_objectSerializer;
};