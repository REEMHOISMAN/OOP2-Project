#include "Strategies/WalkAndJumpStrategy.h"

WalkAndJumpStrategy::WalkAndJumpStrategy(): m_isJumping(false){}

sf::Vector2f& WalkAndJumpStrategy::move(sf::Time deltaTime, bool rightDirection, float gravity)
{
	m_walkTimer -= deltaTime;
	sf::Vector2f newPos;
	float speed;
	gravity == 0 ? speed = deltaTime.asSeconds() * 180.f : speed = 0;
	
	if (m_isJumping)
		newPos.y = -deltaTime.asSeconds() * 600.f + gravity;
	else
		newPos.y = gravity;

	if (rightDirection)
	{
		newPos.x = speed;
	}
	else
	{
		newPos.x = -speed;
	}
	return newPos;
}
