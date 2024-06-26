#include "GameObject/MovingObject/BasicEnemy.h"
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>
#include <iostream>

bool BasicEnemy::m_register = 
	EnemyFactory::registerBasicEnemy(ORANGE_ENEMY,
	[](auto& sprite, auto factor, auto enemyType)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(enemyType);
		setEnemySprite(sprite, factor);
		sprite.setTextureRect(animation[0]);
		return std::make_unique<BasicEnemy>(sprite, std::make_unique<UpDownStrategy>(0.f),
			animation);
	})
	&&
	EnemyFactory::registerBasicEnemy(PEPPER_ENEMY,
	[](auto& sprite, auto factor, auto enemyType)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(enemyType);
		setEnemySprite(sprite, factor);
		sprite.setTextureRect(animation[0]);
		return std::make_unique<BasicEnemy>(sprite, std::make_unique<SideToSideStrategy>(220.f),
			animation);
	})
	&&
	EnemyFactory::registerBasicEnemy(ONION_ENEMY,
	[](auto& sprite, auto factor, auto enemyType)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(enemyType);
		setEnemySprite(sprite, factor);
		sprite.setTextureRect(animation[0]);
		return std::make_unique<BasicEnemy>(sprite, std::make_unique<SideToSideStrategy>(220.f),
			animation);
	});
	


//---------------------------------------------------------
BasicEnemy::BasicEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
	:Enemy(sprite, std::move(strategy)), m_animationIndex(0), m_animation(animation)
{
}

//---------------------------------------------------------
void BasicEnemy::move(sf::Time time)
{
	
	activateGravity(0.3f);
	activateStrategy(time);
	loadAnimationFrame(time);
	setOnGround(false); //<--------- if you put this in "note" the basic enemies movement is being without bugs... 					//           but the orange one jumps to the sky
	setBlockedOnSide(false);
}

void BasicEnemy::loadAnimationFrame(sf::Time deltaTime)
{
	m_elapsed += deltaTime;
	if (m_elapsed.asSeconds() >= 0.3f)
	{
		m_elapsed -= sf::seconds(0.3f);
		++m_animationIndex;
		m_animationIndex %= m_animation.size();
		setTextureRect(m_animation[m_animationIndex]);
	}
}
