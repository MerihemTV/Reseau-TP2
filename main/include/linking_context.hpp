#pragma once

#include <map>
#include "game_object.hpp"

using NetworkID = uint64_t;

class linking_context
{
public:
	using NetworkID = uint64_t;

	linking_context() : m_nextID(1) {}

	std::optional<NetworkID> IDFromGameObject(GameObject* obj);
	std::optional<GameObject*> GameObjectFromID(NetworkID id);

	//return true if insertion went well, false otherwise
	bool addToContext(GameObject* obj, NetworkID id);
	//return true if deletion went well
	bool deleteObject(GameObject* obj);
	//return the NetworkId of GameObject
	NetworkID addObject(GameObject* obj);
private:
	std::map<uint64_t, GameObject*> m_idToObj;
	std::map<GameObject*, uint64_t> m_objToId;

	NetworkID m_nextID;
};