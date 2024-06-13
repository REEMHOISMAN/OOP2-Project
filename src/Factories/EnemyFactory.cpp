#include "Factories/EnemyFactory.h"
#include "Strategies/SideToSideStrategy.h"
#include <vector>

std::unique_ptr<Enemy> EnemyFactory::createSideToSideEnemy(const EnemyType enemy, sf::Sprite& sprite)
{
	std::vector<sf::IntRect> animation = { sf::IntRect({45,50},{54,62}), sf::IntRect({115,50},{54,62}),
											sf::IntRect({188,50},{54,62}) };
	sprite.setTextureRect(animation[0]);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(1.7, 1.7);

	auto it = getMap().find(enemy);
	if (it == getMap().end())
		return nullptr;
	return it->second(sprite, std::move(std::make_unique<SideToSideStrategy>()), animation);
}

bool EnemyFactory::registerEnemy(const EnemyType enemy, 
	createFunc createEnemy)
{
	getMap().emplace(enemy, createEnemy);
	return true;
}

enemyMap& EnemyFactory::getMap()
{
	static enemyMap map;
	return map;
}
