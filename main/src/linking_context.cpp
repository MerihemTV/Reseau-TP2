#include "linking_context.hpp"

bool linking_context::addToContext(GameObject* obj, NetworkID id) {
	auto [it, success] = m_idToObj.insert({ id,obj });
	auto [it2, success2] = m_objToId.insert({ obj,id });
	return (success && success2);
}