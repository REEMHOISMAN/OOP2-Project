#include "DesignPatterns/Strategies/SideToSideStrategy.h"

//----------------------------------------------------
SideToSideStrategy::SideToSideStrategy(float speed): m_speed(speed)
{
}

//----------------------------------------------------
sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection,float gravity)
{
	sf::Vector2f newPos;
	float newX;
	gravity < 0.6f ? newX = deltaTime.asSeconds() * m_speed : newX = 0;
	
	if (rightDirection)
	{
		newPos={ newX,gravity };
	}
	else 
	{
		newPos = {-newX, gravity };
	}
	return newPos;
}

//220.f
