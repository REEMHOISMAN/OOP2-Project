#pragma once
#include <memory>
#include "GameObject/MovingObject/Enemy.h"
#include <map>
#include "Macros.h"

using createFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, std::unique_ptr<MovingStrategy>&&, Animation&);
using enemyMap = std::map<ObjectAnimation, createFunc>;

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>createJumpingEnemy(const ObjectAnimation, sf::Sprite&);
	static std::unique_ptr<Enemy>createSideToSideEnemy(const ObjectAnimation, sf::Sprite&,float);
	static bool registerEnemy(const ObjectAnimation, createFunc);

private:
	static enemyMap& getMap();
};