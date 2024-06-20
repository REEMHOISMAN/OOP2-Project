#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include <vector>

//each time SideToSide enemy is being created -> the ONLY DIFFERENCE is the "ObjectAnimation" that being pass
//for example: "PEPPER_ENEMY" / "PEPPER_ENEMY"
//--------------------------------------------------
std::unique_ptr<Enemy> EnemyFactory::createEnemy(const ObjectAnimation enemy, sf::Sprite& sprite,float factor, InGameState& game)
{
	auto it = getBasicMap().find(enemy);
	if (it != getBasicMap().end())
		return it->second(sprite, factor, enemy);
	
	auto it1 = getPizzaMap().find(enemy);
	if (it1 != getPizzaMap().end())
		return it1->second(sprite, factor, enemy, game);
	
	return nullptr;
}

//--------------------------------------------------
bool EnemyFactory::registerPizzaEnemy(const ObjectAnimation enemy, createPizzaEnemyFunc createEnemy)
{
	getPizzaMap().emplace(enemy, createEnemy);
	return true;
}
//--------------------------------------------------
bool EnemyFactory::registerBasicEnemy(const ObjectAnimation enemy, createBasicEnemyFunc createEnemy)
{
	getBasicMap().emplace(enemy, createEnemy);
	return true;
}

//--------------------------------------------------
pizzaEnemyMap& EnemyFactory::getPizzaMap()
{
	static pizzaEnemyMap map;
	return map;
}

//--------------------------------------------------
basicEnemyMap& EnemyFactory::getBasicMap()
{
	static basicEnemyMap map;
	return map;
}

