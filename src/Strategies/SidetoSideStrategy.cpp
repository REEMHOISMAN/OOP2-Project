#include "Strategies/SidetoSideStrategy.h"

sf::Vector2f& SideToSideStrategy::move(sf::Time deltaTime, bool rightDirection)
{
	sf::Vector2f newPosX;
	auto speed = deltaTime.asSeconds()*150.f;
	if (rightDirection)
	{
		newPosX={ 0,speed };
	}
	else 
	{
		newPosX = { 0,-speed };
	}
	return newPosX;
}
