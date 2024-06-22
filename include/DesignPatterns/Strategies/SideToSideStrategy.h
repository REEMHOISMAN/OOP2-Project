#pragma once
#include "DesignPatterns/Strategies/MovingStrategy.h"

class SideToSideStrategy: public MovingStrategy 
{
public:
	SideToSideStrategy(float speed);
	virtual sf::Vector2f& move(sf::Time deltaTime,bool rightDirection,float gravity)override;

private:
	float m_speed;
};