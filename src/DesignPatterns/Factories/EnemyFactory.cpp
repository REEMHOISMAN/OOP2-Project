#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include <vector>

//--------------------------------------------------
std::unique_ptr<Enemy> EnemyFactory::createEnemy(const sf::Color enemyColor, float x, float y, InGameState* game)
{
	auto it = getEnemyMap().find(enemyColor);
	if (it != getEnemyMap().end())
		return it->second(x, y, game);
	
	return nullptr;
}

//--------------------------------------------------
//bool EnemyFactory::registerEnemy(const ObjectAnimation enemy, createPizzaEnemyFunc createEnemy)
//{
//	getPizzaMap().emplace(enemy, createEnemy);
//	return true;
//}

//--------------------------------------------------
bool EnemyFactory::registerEnemy(const sf::Color color, createEnemyFunc createEnemy)
{
	getEnemyMap().emplace(color, std::move(createEnemy));
	return true;
}

enemyMap& EnemyFactory::getEnemyMap()
{
	static enemyMap map;
	return map;
}
