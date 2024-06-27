#pragma once
#include <memory>
#include "GameObject/MovingObject/Enemy.h"
#include <functional>
#include <map>

class InGameState;
using createEnemyFunc = std::function<std::unique_ptr<MovingObject>(float, float,  InGameState*)>;

struct CompareEnemyColor
{
	bool operator()(const sf::Color color1, const sf::Color color2)const
	{
		return color1.toInteger() < color2.toInteger();
	}
};

using enemyMap = std::map<sf::Color, createEnemyFunc, CompareEnemyColor>;

class EnemyFactory
{
public:
	static std::unique_ptr<MovingObject>createEnemy(const sf::Color, float, float, InGameState*);
	static bool registerEnemy(const sf::Color, createEnemyFunc);

private:
	static enemyMap& getEnemyMap();
};