#pragma once
#include <memory>
#include "GameObject/MovingObject/Enemy.h"
#include <map>

class InGameState;
using createFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, float, const ObjectAnimation);
using enemyMap = std::map<ObjectAnimation, createFunc>;

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>createEnemy(const ObjectAnimation, sf::Sprite&, float);
	static bool registerEnemy(const ObjectAnimation, createFunc);

private:
	static enemyMap& getMap();
};