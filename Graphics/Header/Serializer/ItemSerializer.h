#pragma once
#include "../External/json.hpp"

template <class T>
class ItemSerializer
{
public:
	virtual nlohmann::json Serialize(T item) {
		nlohmann::json empty;
		return empty;
	}

	virtual T Deserialize(nlohmann::json data) {
		return *(T*)0;
	}
};