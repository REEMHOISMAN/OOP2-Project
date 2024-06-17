#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <vector>

//each time SideToSide enemy is being created -> the ONLY DIFFERENCE is the "ObjectAnimation" that being pass
//for example: "PEPPER_ENEMY" / "PEPPER_ENEMY"
//--------------------------------------------------
std::unique_ptr<Enemy> EnemyFactory::createSideToSideEnemy(const ObjectAnimation enemy, sf::Sprite& sprite,float factor)
{
	std::vector<sf::IntRect> animation = ResourceManager::instance().getAnimation(enemy);
	sprite.setTextureRect(animation[0]);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(factor, factor);

	auto it = getMap().find(enemy);
	if (it == getMap().end())
		return nullptr;
	return it->second(sprite, std::move(std::make_unique<SideToSideStrategy>()), animation);
}
//--------------------------------------------------
std::unique_ptr<Enemy> EnemyFactory::createJumpingEnemy(const ObjectAnimation enemy, sf::Sprite& sprite)
{
	std::vector<sf::IntRect> animation = ResourceManager::instance().getAnimation(enemy);
	sprite.setTextureRect(animation[0]);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(1.9, 1.9);

	auto it = getMap().find(enemy);
	if (it == getMap().end())
		return nullptr;
	return it->second(sprite, std::move(std::make_unique<UpDownStrategy>(0.f)), animation);
}

//--------------------------------------------------
bool EnemyFactory::registerEnemy(const ObjectAnimation enemy, 
	createFunc createEnemy)
{
	getMap().emplace(enemy, createEnemy);
	return true;
}

//--------------------------------------------------
enemyMap& EnemyFactory::getMap()
{
	static enemyMap map;
	return map;
}
