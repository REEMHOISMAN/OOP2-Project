#include "GameObject/MovingObject/BasicEnemy.h"
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>

bool BasicEnemy::m_register =
	EnemyFactory::registerEnemy(ORANGE_ENEMY,
	[](auto& sprite, auto factor, auto enemyType)->std::unique_ptr<Enemy>
	{
		setEnemySprite(sprite, scale);
		return std::make_unique<BasicEnemy>(sprite, std::make_unique<UpDownStrategy>(),
			ResourceManager::instance().getAnimation(enemyType));
	})
	&&
	EnemyFactory::registerEnemy(ORANGE_ENEMY,
	[](auto& sprite, auto factor, auto enemyType)->std::unique_ptr<Enemy>
	{
		setEnemySprite(sprite, scale);
		return std::make_unique<BasicEnemy>(sprite, std::make_unique<UpDownStrategy>(),
			ResourceManager::instance().getAnimation(enemyType));
	})
	&&


//---------------------------------------------------------
BasicEnemy::BasicEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
	:Enemy(sprite,std::move(strategy),animation)
{
}

//---------------------------------------------------------
void BasicEnemy::move(sf::Time time)
{
	if (!isOnGround())
		activateGravity(0.3f);

	else
		resetGravity();

	auto newPos = getStrategy()->move(time, isHeadDirectionRight(), getGravity());

	setObjectPosition(newPos + getObjectSprite().getPosition());
	loadAnimationFrame(time);
	setOnGround(false);
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
