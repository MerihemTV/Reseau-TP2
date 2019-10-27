#pragma once
#include <map>
#include <functional>
#include <cassert>
#include "game_object.hpp"

class ClassRegistry
{
public:
	using GameObjectInitializer = std::function<GameObject* ()>;

	static ClassRegistry& getInstance() {
		static ClassRegistry instance;
		return instance;
	}

	template<class T>
	void saveClassInRegistry()
	{
		static_assert(std::is_base_of<GameObject, T>::value);
		assert(m_initializers.find(T::mClassID) == m_initializers.end());
		m_initializers[T::mClassID] = T::CreateInstance;
	}

	GameObject* Create(ReplicationClassID classID)
	{
		assert(m_initializers.find(classID) != m_initializers.end());
		auto gameObj = m_initializers[classID]();
		return gameObj;
	}

	ClassRegistry(ClassRegistry const&) = delete;
	void operator=(ClassRegistry const&) = delete;

private:
	ClassRegistry() {}	// Constructor
	std::map<ReplicationClassID, GameObjectInitializer> m_initializers;		// Link Class IDs with their construct pointer
};
