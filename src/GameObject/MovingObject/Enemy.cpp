#include "GameObject/MovingObject/Enemy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation) :
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

std::unique_ptr<MovingStrategy> Enemy::getStrategy() 
{
	return std::move(m_moveStrategy);
}