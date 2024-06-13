#include "Strategies/SideToSideStrategy.h"

sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection,float gravity)
{
	sf::Vector2f newPosX;
	auto speed = deltaTime.asSeconds()*200.f;
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
