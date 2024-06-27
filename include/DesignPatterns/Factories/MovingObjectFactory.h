#pragma once
#include <memory>
#include "GameObject/MovingObject/MovingObject.h"
#include <functional>
#include <map>
#include "Macros.h"

class Level;
using MovingObjectFunc = std::function<std::unique_ptr<MovingObject>(float, float,  Level*)>;



using movingObjectMap = std::map<sf::Color, MovingObjectFunc, CompareColor>;

class MovingObjectFactory
{
public:
	static std::unique_ptr<MovingObject>createMovingObject(const sf::Color, float, float, Level*);
	static bool registerMovingObject(const sf::Color, MovingObjectFunc);

private:
	static movingObjectMap& getMovingObjectMap();
};