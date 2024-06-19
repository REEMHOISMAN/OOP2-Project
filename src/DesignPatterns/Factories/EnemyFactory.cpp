#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include <vector>

//each time SideToSide enemy is being created -> the ONLY DIFFERENCE is the "ObjectAnimation" that being pass
//for example: "PEPPER_ENEMY" / "PEPPER_ENEMY"
//--------------------------------------------------
std::unique_ptr<Enemy> EnemyFactory::createEnemy(const ObjectAnimation enemy, sf::Sprite& sprite,float factor)
{
	auto it = getMap().find(enemy);
	if (it == getMap().end())
		return nullptr;
	return it->second(sprite, factor, enemy);
}
//--------------------------------------------------
bool EnemyFactory::registerEnemy(const ObjectAnimation enemy, 
	createFunc createEnemy)
{
	getMap().emplace(enemy, createEnemy);
	return true;
}

//--------------------------------------------------
enemyMap& EnemyFactory::getMap()
{
	static enemyMap map;
	return map;
}
