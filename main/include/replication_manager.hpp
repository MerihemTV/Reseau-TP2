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
	void Replicate(OutputStream& stream, const std::vector<GameObject*>& objectsToReplicate);
	void Replicate(InputStream& stream);

	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);

private:
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