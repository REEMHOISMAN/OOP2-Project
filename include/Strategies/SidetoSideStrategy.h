#pragma once
#include"Strategies/MovingStrategy.h"

class SideToSideStrategy: public MovingStrategy 
{
public:
	SideToSideStrategy() = default;
	virtual sf::Vector2f& move(sf::Time deltaTime,bool rightDirection)override;
};