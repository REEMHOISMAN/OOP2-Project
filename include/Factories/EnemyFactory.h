#pragma once
#include <memory>
#include "Enemy.h"
#include <map>
#include "Macros.h"

using createFunc = std::unique_ptr<Enemy>(*)(sf::Sprite&, std::unique_ptr<MovingStrategy>&&, Animation&);
using enemyMap = std::map<EnemyType, createFunc>;

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>createSideToSideEnemy(const EnemyType, sf::Sprite&);
	static bool registerEnemy(const EnemyType, createFunc);

private:
	static enemyMap& getMap();
};