#pragma once

#include <map>
#include <optional>
#include "game_object.hpp"

class LinkingContext
{
public:
	using NetworkID = uint64_t;

	LinkingContext() : m_nextID(1) {}

	std::optional<NetworkID> IDFromGameObject(GameObject* obj);
	std::optional<GameObject*> GameObjectFromID(NetworkID id);

	bool addObject(GameObject* obj, NetworkID id);			// Add GameObject to context from Network		Returns true if insertion wen well, false otherwise
	NetworkID addObject(GameObject* obj);					// Add GameObject to context from GamePlay		Returns the NetworkID associated to the GameObject
	bool deleteObject(GameObject* obj);						// Delete GameObject from context				Returns true if deletion went well

private:
	std::map<NetworkID, GameObject*> m_idToObj;
	std::map<GameObject*, NetworkID> m_objToId;

	NetworkID m_nextID;
};