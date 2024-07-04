#pragma once
#include"DesignPatterns/Strategies/MovingStrategy.h"

class UpDownStrategy : public MovingStrategy
{
public:
	UpDownStrategy(float);
	virtual const sf::Vector2f move(sf::Time deltaTime,bool rightDirection, float gravity)override;

private:
	float m_posX;
};