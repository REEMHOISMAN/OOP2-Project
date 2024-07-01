#include "DesignPatterns/Factories/StaticObjectFactory.h"

/*================== createStaticObject =================*/
std::unique_ptr<StaticObject> StaticObjectFactory::createStaticObject(const sf::Color objectColor, float x, float y)
{
	auto it = getStaicObjectMap().find(objectColor);
	if (it != getStaicObjectMap().end())
		return it->second(x, y);

	return nullptr;
}

/*================== registerStaticObject =================*/
bool StaticObjectFactory::registerStaticObject(const sf::Color color, StaticObjectFunc createStaticObject)
{
	getStaicObjectMap().emplace(color, std::move(createStaticObject));
	return true;
}

/*================== getStaicObjectMap =================*/
StaticObjectMap& StaticObjectFactory::getStaicObjectMap()
{
	static StaticObjectMap map;
	return map;
}
