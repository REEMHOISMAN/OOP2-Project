#include "DesignPatterns/Strategies/SideToSideStrategy.h"

sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection,float gravity)
{
	sf::Vector2f newPosX;
	float speed;
	gravity < 1.8f ? speed = deltaTime.asSeconds() * 220.f : speed = 0;
	
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
