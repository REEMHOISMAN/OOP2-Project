#pragma once
#include <memory>
#include "GameObject/MovingObject/Enemy.h"
#include <functional>
#include <map>

class InGameState;
using createEnemyFunc = std::function<std::unique_ptr<Enemy>(float, float,  InGameState*)>;
//using enemyMap = std::map<sf::Color, createEnemyFunc>;


struct CompareEnemyColor
{
	bool operator()(const sf::Color color1, const sf::Color color2)const
	{
		return color1.toInteger() < color2.toInteger();
	}
};
//using createPizzaEnemyFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, float, const ObjectAnimation, InGameState&);
//using createBasicEnemyFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, float, const ObjectAnimation);

using enemyMap = std::map<sf::Color, createEnemyFunc, CompareEnemyColor>;

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>createEnemy(const sf::Color, float, float, InGameState* = nullptr);
	static bool registerEnemy(const sf::Color, createEnemyFunc);

private:
	static enemyMap& getEnemyMap();
};