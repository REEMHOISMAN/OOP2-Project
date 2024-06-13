#include "Strategies/SideToSideStrategy.h"

sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection,float gravity)
{
	sf::Vector2f newPosX;
	float speed;
	gravity!=0?speed=0.f:speed = deltaTime.asSeconds() * 250.f;
	
	if (rightDirection)
	{
		newPosX={speed,gravity };
	}
	else 
	{
		newPosX = {-speed, gravity };
	}
	return newPosX;
}
