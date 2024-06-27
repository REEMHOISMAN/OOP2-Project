#pragma once
#include <memory>
#include "GameObject/MovingObject/Enemy.h"
#include <functional>
#include <map>

class InGameState;
using MovingObjectFunc = std::function<std::unique_ptr<MovingObject>(float, float,  InGameState*)>;

struct CompareColor
{
	bool operator()(const sf::Color color1, const sf::Color color2)const
	{
		return color1.toInteger() < color2.toInteger();
	}
};

using enemyMap = std::map<sf::Color, MovingObjectFunc, CompareColor>;

class MovingObjectFactory
{
public:
	static std::unique_ptr<MovingObject>createMovingObject(const sf::Color, float, float, InGameState*);
	static bool registerMovingObject(const sf::Color, MovingObjectFunc);

private:
	static enemyMap& getEnemyMap();
};