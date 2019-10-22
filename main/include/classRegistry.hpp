//mClassID étant le nom de la valeur de l’enum de votre identifiant de classe => ex ENEM ou PLAY ou GOBJ
#include <map>
#include "game_object.hpp"
#include <vector>
#include <string>
#include <functional>
class classRegistry
{
public:

	template<typename T>
	static void saveClassInRegistry(std::function<GameObject()> f) {
		idToConstructor.insert({ T::mClassID, f });
	};

	GameObject create(int id) {
		std::function<GameObject()> Constructor = idToConstructor.find(id)->second;
		GameObject result = Constructor();
		return(result);
	}

private:
	//lie des identifiants de classes avec les pointeurs des constructeurs
	std::map<int, std::function <GameObject()>> idToConstructor; 
};
