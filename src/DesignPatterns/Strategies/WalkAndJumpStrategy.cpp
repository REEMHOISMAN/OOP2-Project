#include "DesignPatterns/Strategies/WalkAndJumpStrategy.h"

WalkAndJumpStrategy::WalkAndJumpStrategy(): m_isJumping(false), m_walkTimer(sf::seconds(0.6f)){}

sf::Vector2f& WalkAndJumpStrategy::move(sf::Time deltaTime, bool rightDirection, float gravity)
{
	m_walkTimer -= deltaTime;
	
	sf::Vector2f newPos;
	float speed;
	gravity < 1.8f ? speed = deltaTime.asSeconds() * 180.f : speed = 0;
	
	if (m_isJumping){
		newPos.y = -deltaTime.asSeconds() * 600.f + gravity;
		m_walkTimer = sf::seconds(0.6f);
	}
		
	else {
		newPos.y = gravity;
	}


	rightDirection ? newPos.x = speed : newPos.x = -speed;

	if (m_walkTimer.asSeconds() <= 0.f){
		m_isJumping == true;
	}

	return newPos;
}

void WalkAndJumpStrategy::resetIsJumping()
{
	m_isJumping = false;
}