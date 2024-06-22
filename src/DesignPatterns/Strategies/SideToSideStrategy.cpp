#include "DesignPatterns/Strategies/SideToSideStrategy.h"

//----------------------------------------------------
SideToSideStrategy::SideToSideStrategy(float speed,float height): m_speed(speed),m_height(height)
{
}

//----------------------------------------------------
sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection,float gravity)
{
	sf::Vector2f newPos;
	float newX;
	//gravity < 0.6f ? newX = deltaTime.asSeconds() * m_speed : newX = 0;
	newX = deltaTime.asSeconds() * m_speed;
	if (rightDirection)
	{
	    newPos={ newX,m_height+gravity};
	}
	else 
	{
		newPos = {-newX, m_height+gravity};
	}
	return newPos;
}

//220.f
