#pragma once
#include"Strategies/MovingStrategy.h"

class UpDownStrategy : public 
	MovingStrategy

{
public:
	UpDownStrategy(float);
	virtual sf::Vector2f& move(sf::Time deltaTime,bool rightDirection, float gravity)override;

private:
	float m_posX;
	float m_jumpHeight;
};