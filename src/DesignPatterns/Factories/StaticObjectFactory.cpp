#include "DesignPatterns/Factories/StaticObjectFactory.h"

std::unique_ptr<StaticObject> StaticObjectFactory::createStaticObject(const sf::Color objectColor, float x, float y)
{
	auto it = getStaicObjectMap().find(objectColor);
	if (it != getStaicObjectMap().end())
		return it->second(x, y);

	return nullptr;
}

bool StaticObjectFactory::registerStaticObject(const sf::Color color, StaticObjectFunc createStaticObject)
{
	getStaicObjectMap().emplace(color, std::move(createStaticObject));
	return true;
}

StaticObjectMap& StaticObjectFactory::getStaicObjectMap()
{
	static StaticObjectMap map;
	return map;
}
