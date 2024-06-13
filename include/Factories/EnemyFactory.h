#pragma once
#include <memory>
#include "Enemy.h"

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>BasicEnemy(sf::Sprite animation);
	//static std::unique_ptr<Enemy>createPizzaEnemy(sf::Sprite animation);
};