#include "linking_context.hpp"

bool linking_context::addToContext(GameObject* obj, NetworkID id) {
	auto [it, success] = m_idToObj.insert({ id,obj });
	auto [it2, success2] = m_objToId.insert({ obj,id });
	return (success && success2);
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