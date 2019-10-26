#pragma once

#include <cstdint>
#include <vector>
#include <unordered_set>
#include "streams.hpp"
#include "game_object.hpp"

#include "linking_context.hpp"
#include "class_registry.hpp"

class ReplicationManager {

	static constexpr uint32_t ms_protocolID = 0xDECEA5ED;

public:
	static ReplicationManager& getInstance() {
		static ReplicationManager instance;
		return instance;
	}

	void Replicate(OutputStream& stream, const std::vector<GameObject*>& objectsToReplicate);
	void Replicate(InputStream& stream);

	void AddObject(GameObject* object, LinkingContext::NetworkID objectID);
	void RemoveObject(GameObject* object);

	std::unordered_set<GameObject*> getReplicatedObjects()
	{
		return m_replicatedObjects;
	}

	ReplicationManager(ClassRegistry const&) = delete;
	void operator=(ReplicationManager const&) = delete;

private:
	ReplicationManager() { m_context = LinkingContext(); };

	LinkingContext m_context;

	enum class PacketType : uint8_t
	{
		Hello = 0x00,
		Sync = 0x01,
		Bye = 0x02,
		PacketType_MAX
	};

	std::unordered_set<GameObject*> m_replicatedObjects;
};