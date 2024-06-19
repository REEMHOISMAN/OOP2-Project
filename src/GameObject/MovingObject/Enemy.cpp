#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy) :
	Entity(sprite), m_moveStrategy(std::move(strategy))
{
	
}

//---------------------------------------------------
void Enemy::setStrategy(std::unique_ptr<MovingStrategy> strategy)
{
	m_moveStrategy = std::move(strategy);
}
//---------------------------------------------------
void Enemy::setEnemySprite(sf::Sprite& sprite, float factor)
{
	
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(factor, factor);
}

void Enemy::activateStrategy(sf::Time time)
{
	auto newPos= m_moveStrategy->move(time, isHeadDirectionRight(), getGravity());
	setObjectPosition(newPos + getObjectSprite().getPosition());
}