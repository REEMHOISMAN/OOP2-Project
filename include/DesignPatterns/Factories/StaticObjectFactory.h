#pragma once 

#include "GameObject/StaticObject/StaticObject.h"
#include <map>
#include <memory>
#include "Macros.h"
#include <functional>

using StaticObjectFunc = std::function<std::unique_ptr< StaticObject>(float, float)>;
using StaticObjectMap = std::map<sf::Color, StaticObjectFunc, CompareColor>;

class StaticObjectFactory 
{
public:
	static std::unique_ptr<StaticObject>createStaticObject(const sf::Color, float, float);
	static bool registerStaticObject(const sf::Color, StaticObjectFunc);
private:
	static StaticObjectMap& getStaicObjectMap();
};