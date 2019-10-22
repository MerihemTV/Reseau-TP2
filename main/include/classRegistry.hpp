#include <map>
#include "game_object.hpp"
#include <vector>
#include <string>
#include <functional>
class classRegistry
{
public:

	static classRegistry* get() {
		if (singleton==NULL) {
			singleton = new classRegistry();
		}
		return singleton;
	}

	~classRegistry();

	template<typename T>
	void saveClassInRegistry(std::function<GameObject()> f) {
		idToConstructor.insert({T::mClassID,f});
	};

	GameObject create(int id) {
		std::function<GameObject()> Constructor = idToConstructor.find(id)->second;
		GameObject result = Constructor();
		return(result);
	}

private:
	classRegistry() {};
	//lie des identifiants de classes avec les pointeurs des constructeurs
	std::map<int, std::function <GameObject()>> idToConstructor; 

	static classRegistry* singleton;
};
