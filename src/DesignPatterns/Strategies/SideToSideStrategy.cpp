#include "DesignPatterns/Strategies/SideToSideStrategy.h"

/*================== SideToSideStrategy Constructor =================*/
SideToSideStrategy::SideToSideStrategy(float speed,float height): m_speed(speed),m_height(height)
{
}

/*================== SideToSideStrategy move =================*/
const sf::Vector2f SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection,float gravity)
{
	sf::Vector2f newPos;
	float newX;
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

