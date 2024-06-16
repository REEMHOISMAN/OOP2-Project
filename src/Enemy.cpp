#include "Enemy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation):
	Entity(sprite), m_moveStrategy(std::move(strategy)), m_animation(animation),m_animationIndex(0){}

void Enemy::move(sf::Time time)
{
	if (!isOnGround())
		activateGravity(0.3f);

	else
		resetGravity();

	auto newPos = m_moveStrategy->move(time, isHeadDirectionRight(), getGravity());
	
	setObjectPosition(newPos + getObjectSprite().getPosition());
	loadAnimation(time);
	setOnGround(false);
	
}

void Enemy::loadAnimation(sf::Time time)
{
	sf::Time animationTime = sf::seconds(0.1f);
	m_elapsed += time;
	if (m_elapsed >= animationTime)
	{
		m_elapsed -= animationTime;
		++m_animationIndex;
		m_animationIndex %= m_animation.size();
		setTextureRect(m_animation[m_animationIndex]);
	}
}
