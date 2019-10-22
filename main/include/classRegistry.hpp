#include <map>
#include "game_object.hpp"
#include <vector>
#include <string>
#include <functional>
class classRegistry
{
public:

	static classRegistry& getInstance() {
		static classRegistry instance;
		return instance;
	}

	template<typename T>
	void saveClassInRegistry() {
		idToConstructor.emplace(T::mClassID,T::CreateInstance);
	};

	GameObject* create(int id) {
		std::function<GameObject*()> Constructor = idToConstructor.find(id)->second;
		GameObject* result = Constructor();
		return(result);
	}

	classRegistry(classRegistry const&) = delete;
	void operator=(classRegistry const&) = delete;
private:
	classRegistry() {};
	//lie des identifiants de classes avec les pointeurs des constructeurs
	std::map<int, std::function<GameObject*()>> idToConstructor; 
};
