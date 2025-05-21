#pragma once
#include "ItemSerializer.h"
#include "../../Header/Scene/Shape/Object.h"

template <class T>
class KeyedItemSerializer : public ItemSerializer<T>
{
public:
	KeyedItemSerializer(std::map<std::string, ItemSerializer<T>*>* objects) {
		m_objects = objects;
	}

	nlohmann::json Serialize(T item) {
		std::string key = SerializerId::Id[typeid(item)];
		if (m_objects->find(key) == m_objects->end()) return nlohmann::json();
		return (*m_objects)[key]->Serialize(item);
	}

	T Deserialize(nlohmann::json parentData) {
		for (auto it = parentData.begin(); it != parentData.end(); ++it) {
			if (m_objects->find(it.key()) == m_objects->end()) continue;		
			return (*m_objects)[it.key()]->Deserialize(parentData[it.key()]);
		}
	}
private:
	std::map<std::string, ItemSerializer<T>*>* m_objects;
};