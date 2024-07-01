#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "Level.h"
#include <vector>

/*================== createMovingObject =================*/
std::unique_ptr<MovingObject> MovingObjectFactory::createMovingObject(const sf::Color enemyColor, float x, float y, Level* level)
{
	auto it = getMovingObjectMap().find(enemyColor);
	if (it != getMovingObjectMap().end())
		return it->second(x, y, level);
	
	return nullptr;
}

/*================== registerMovingObject =================*/
/**----------------------------------------------
 * each game object have unique color as key, and it create function as value
 *---------------------------------------------**/
bool MovingObjectFactory::registerMovingObject(const sf::Color color, MovingObjectFunc createMovingObject)
{
	getMovingObjectMap().emplace(color, std::move(createMovingObject));
	return true;
}

/*================== getMovingObjectMap =================*/
movingObjectMap& MovingObjectFactory::getMovingObjectMap()
{
	static movingObjectMap map;
	return map;
}
