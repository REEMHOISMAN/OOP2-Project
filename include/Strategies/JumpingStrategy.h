#pragma once
#include"Strategies/MovingStrategy.h"

class JumpingStrategy : public MovingStrategy
{
public:
	JumpingStrategy() = default;
	virtual sf::Vector2f& move(sf::Time deltaTime,bool rightDirection, float gravity)override;
};