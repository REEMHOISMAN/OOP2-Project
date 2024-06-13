#include "Factories/EnemyFactory.h"
#include "Strategies/MovingStrategy.h"
#include <vector>

std::unique_ptr<Enemy> EnemyFactory::createSideToSideEnemy(const EnemyType enemy, sf::Sprite& sprite)
{
	std::vector<sf::IntRect> animation = { sf::IntRect({45,50},{54,62}), sf::IntRect({115,50},{54,62}),
											sf::IntRect({188,50},{54,62}) };

	auto it = getMap().find(enemy);
	if (it == getMap().end())
		return nullptr;
	return it->second(sprite, std::make_unique<MovingStrategy>(), animation);
}

bool EnemyFactory::registerEnemy(const EnemyType enemy, 
	std::unique_ptr<Enemy>(*createEnemy)(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&))
{
	getMap().emplace(enemy, createEnemy);
	return true;
}
