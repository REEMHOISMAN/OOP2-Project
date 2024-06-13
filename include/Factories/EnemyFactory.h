#pragma once
#include <memory>
#include "Enemy.h"


//add enum -> 
class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>SideToSideEnemy(sf::Sprite&);
	//static std::unique_ptr<Enemy>createPizzaEnemy(sf::Sprite animation);
};