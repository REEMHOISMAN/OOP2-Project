#include "Enemy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation):
	Entity(sprite), m_moveStrategy(std::move(strategy)), m_animation(animation){}

void Enemy::move(sf::Time time)
{
	auto newPos = m_moveStrategy->move(time, isHeadDirectionRight());
	setObjectPosition(newPos + getObjectSprite().getPosition());
}
