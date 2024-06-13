#include "Enemy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation):
	Entity(sprite), m_moveStrategy(std::move(strategy)), m_animation(animation),m_gravity(0){}

void Enemy::move(sf::Time time)
{
	activateGravity();
	auto newPos = m_moveStrategy->move(time, isHeadDirectionRight(),m_gravity);
	setObjectPosition(newPos + getObjectSprite().getPosition());
}

void Enemy::activateGravity()
{
	if (!getColideData()) {
		m_gravity += 0.3f;
	}
	else {
		m_gravity = 0;
	}
}
