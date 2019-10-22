#include "linking_context.hpp"

#include <iostream>

bool linking_context::addToContext(GameObject* obj, NetworkID id) {
	auto is_obj_existing = GameObjectFromID(id);
	auto is_id_existing = IDFromGameObject(obj);

	if (is_obj_existing != std::nullopt || is_id_existing != std::nullopt) {
		return false;
	}
	else {
		m_idToObj.insert({ id,obj });
		m_objToId.insert({ obj,id });
		return true;
	}
	
}

std::optional<NetworkID> linking_context::IDFromGameObject(GameObject* obj) {
	auto itFind = m_objToId.find(obj);
	if (itFind != m_objToId.end()) {
		return itFind->second;
	}
	else {
		return std::nullopt;
	}
}

std::optional<GameObject *> linking_context::GameObjectFromID(NetworkID id) {
	auto itFind = m_idToObj.find(id);
	if (itFind != m_idToObj.end()) {
		return itFind->second;
	}
	else {
		return std::nullopt;
	}
}


//return true if deletion went well
bool linking_context::deleteObject(GameObject* obj) {
	auto ID = IDFromGameObject(obj);
	int i = 0;
	i += m_idToObj.erase(ID.value());
	i += m_objToId.erase(obj);
	return (i == 2);
};

//return the NetworkId of GameObject
NetworkID linking_context::addObject(GameObject* obj) {
	auto ID = IDFromGameObject(obj);
	if (ID == std::nullopt) {
		addToContext(obj, m_nextID);
		return(m_nextID++);
	}
	else {
		return ID.value();
	}
};