#pragma once
#include <memory>
#include "GameObject/MovingObject/Enemy.h"
#include <map>

class InGameState;
using createPizzaEnemyFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, float, const ObjectAnimation, InGameState&);
using createBasicEnemyFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, float, const ObjectAnimation);

using pizzaEnemyMap = std::map<ObjectAnimation, createPizzaEnemyFunc>;
using basicEnemyMap = std::map<ObjectAnimation, createBasicEnemyFunc>;

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>createEnemy(const ObjectAnimation, sf::Sprite&, float, InGameState&);
	static bool registerBasicEnemy(const ObjectAnimation, createBasicEnemyFunc);
	static bool registerPizzaEnemy(const ObjectAnimation, createPizzaEnemyFunc);

private:
	static basicEnemyMap& getBasicMap();
	static pizzaEnemyMap& getPizzaMap();
};