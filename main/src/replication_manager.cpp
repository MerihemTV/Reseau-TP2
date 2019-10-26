#include "replication_manager.hpp"

void ReplicationManager::Replicate(OutputStream& stream, const std::vector<GameObject*>& objectsToReplicate)
{
	// Protocol ID Writing
	stream.Write(ReplicationManager::ms_protocolID);

	// Packet Type Writing
	auto type = to_integral(PacketType::Sync);
	stream.Write(type);

	for (auto gameObj : objectsToReplicate)
	{
		// Object ID Writing
		auto objectID = m_context.IDFromGameObject(gameObj);
		if (!objectID) objectID = m_context.addObject(gameObj);
		stream.Write(*objectID);
		// Class ID Writing
		auto classID = gameObj->ClassID();
		stream.Write(classID);
		// Object Writing
		gameObj->Write(stream);
	}
}
void ReplicationManager::Replicate(InputStream& stream)
{
	// Protocol ID Reading
	uint32_t protocolID = stream.Read<uint32_t>();
	if (protocolID != ms_protocolID) return;

	// Packet Type Reading
	uint8_t packetType = stream.Read<uint8_t>();
	if (packetType != to_integral(PacketType::Sync)) return;

	std::unordered_set<GameObject*> receivedObjects;

	while (stream.RemainingSize() > 0)
	{
		// Object and Class ID Reading
		LinkingContext::NetworkID objID = stream.Read<LinkingContext::NetworkID>();
		ReplicationClassID classID = stream.Read<ReplicationClassID>();

		// Object Reading
		auto gameObj = m_context.GameObjectFromID(objID);

		// Non-existing object in linking context
		if (!gameObj)
		{
			GameObject* objCreated = ClassRegistry::getInstance().Create(classID);
			objCreated->Read(stream);
			AddObject(objCreated, objID);
			receivedObjects.insert(objCreated);
		}

		// Existing object in linking context
		else
		{
			gameObj.value()->Read(stream);
			receivedObjects.insert(gameObj.value());
		}

		// Remove objects to be removed
		if (receivedObjects != m_replicatedObjects)
		{
			std::vector<GameObject*> objectsToDestroy;
			std::copy_if(m_replicatedObjects.begin(), m_replicatedObjects.end(), std::back_inserter(objectsToDestroy),
				[&receivedObjects](GameObject* object) { return receivedObjects.find(object) == receivedObjects.end(); });
			for (auto object : objectsToDestroy)
			{
				RemoveObject(object);
			}
		}
	}
}

void ReplicationManager::AddObject(GameObject* object, LinkingContext::NetworkID objectID)
{
	m_context.addObject(object, objectID);
	m_replicatedObjects.insert(object);
}
void ReplicationManager::RemoveObject(GameObject* object)
{
	m_context.deleteObject(object);
	m_replicatedObjects.erase(object);
	object->Destroy();
}