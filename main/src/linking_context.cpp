#include "linking_context.hpp"

#include <iostream>

std::optional<LinkingContext::NetworkID> LinkingContext::IDFromGameObject(GameObject* obj) {
	auto itFind = m_objToId.find(obj);
	if (itFind != m_objToId.end()) {
		return itFind->second;
	}
	else {
		return std::nullopt;
	}
}

std::optional<GameObject *> LinkingContext::GameObjectFromID(NetworkID id) {
	auto itFind = m_idToObj.find(id);
	if (itFind != m_idToObj.end()) {
		return itFind->second;
	}
	else {
		return std::nullopt;
	}
}


// Add GameObject to context from Network	-	Returns true if insertion wen well, false otherwise
bool LinkingContext::addObject(GameObject* obj, NetworkID id) {
	auto is_obj_existing = GameObjectFromID(id);
	auto is_id_existing = IDFromGameObject(obj);

	if (is_obj_existing != std::nullopt || is_id_existing != std::nullopt) {
		return false;
	}
	else{
		m_idToObj.insert({ id,obj });
		m_objToId.insert({ obj,id });
		m_nextID = id++;
		return true;
	}
}

// Add GameObject to context from GamePlay	-	Returns the NetworkID associated to the GameObject
LinkingContext::NetworkID LinkingContext::addObject(GameObject* obj) {
	auto ID = IDFromGameObject(obj);
	if (ID == std::nullopt) {
		addObject(obj, m_nextID);
		return(m_nextID++);
	}
	else {
		return ID.value();
	}
};

// Delete GameObject from context	-	Returns true if deletion went well
bool LinkingContext::deleteObject(GameObject* obj) {
	auto ID = IDFromGameObject(obj);
	int i = 0;
	if (ID != std::nullopt) {
		i += m_idToObj.erase(ID.value());
		i += m_objToId.erase(obj);
		return (i == 2);
	}
	else {
		return false;
	}
}