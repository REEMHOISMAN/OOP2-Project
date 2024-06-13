#pragma once
#include"Strategies/MovingStrategy.h"

class SideToSideStrategy:MovingStrategy 
{
public:
	virtual sf::Vector2f& move(sf::Time deltaTime,bool rightDirection)override;
};