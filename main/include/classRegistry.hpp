//mClassID étant le nom de la valeur de l’enum de votre identifiant de classe => ex ENEM ou PLAY ou GOBJ
#include <map>
#include "player.hpp"
#include "enemy.hpp"
#include "game_object.hpp"
#include <vector>
#include <string>
class classRegistry
{
public:


private:
	//Le constructeur sera en private
	std::map<int, std::function <void>> idToConstructor; //lie des identifiants de classes avec les pointeurs des constructeurs

	idToConstructor.emplace(0, &Player::Player); //Player ('PLAY')
	idToConstructor.emplace(1, &Enemy::Enemy); //Enemy ('ENEM')
	
	std::vector<GameObject> registry; //??????

	template<typename T>
	int mClassID(std::string idStr) {
		if (idStr == 'PLAY'){
			return 0
		}
		if (idStr == 'ENEM') {
			return 1
		}
		else {
			EXIT_FAILURE;
		}
	}
	//mais T::mClassID est la manière d'accéder	à l'ID de classe => fonction qui prend un mClassID en paramètre ?
	saveClassInRegistry(std::string mClassID) //mClassID = 'PLAY' ou 'ENEM'
	{

		registry.insert(mClassID);
	};
	auto Create() { //prend en paramètre un id de classe et retourne le GameObject
	}
};
