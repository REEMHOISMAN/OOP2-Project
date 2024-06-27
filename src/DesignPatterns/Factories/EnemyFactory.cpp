#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include <vector>

//--------------------------------------------------
std::unique_ptr<MovingObject> MovingObjectFactory::createMovingObject(const sf::Color enemyColor, float x, float y, InGameState* game)
{
	auto it = getMovingObjectMap().find(enemyColor);
	if (it != getMovingObjectMap().end())
		return it->second(x, y, game);
	
	return nullptr;
}

//--------------------------------------------------
bool MovingObjectFactory::registerMovingObject(const sf::Color color, MovingObjectFunc createMovingObject)
{
	getMovingObjectMap().emplace(color, std::move(createMovingObject));
	return true;
}

movingObjectMap& MovingObjectFactory::getMovingObjectMap()
{
	static movingObjectMap map;
	return map;
}
