#include "Enemy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation):
	Entity(sprite), m_moveStrategy(std::move(strategy)), m_animation(animation),m_gravity(0){}

void Enemy::move(sf::Time time)
{
	activateGravity();
	auto newPos = m_moveStrategy->move(time, isHeadDirectionRight(),m_gravity);
	setObjectPosition(newPos + getObjectSprite().getPosition());
	loadAnimation(time);
}

void Enemy::activateGravity()
{
	if (!getColideData()) {
		m_gravity += 0.2f;
	}
	else {
		m_gravity = 0;
	}
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
