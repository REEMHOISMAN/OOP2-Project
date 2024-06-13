#include "Strategies/SideToSideStrategy.h"

sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection)
{
	sf::Vector2f newPosX;
	auto speed = deltaTime.asSeconds()*200.f;
	if (rightDirection)
	{
		newPosX={speed,0 };
	}
	else 
	{
		newPosX = {-speed, 0 };
	}
	return newPosX;
}
