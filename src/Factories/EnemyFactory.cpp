#include "Factories/EnemyFactory.h"
#include "Strategies/MovingStrategy.h"

std::unique_ptr<Enemy> EnemyFactory::SideToSideEnemy(sf::Sprite& animation)
{
	return std::unique_ptr<Enemy>();
}
