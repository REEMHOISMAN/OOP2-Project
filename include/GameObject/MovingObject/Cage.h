#pragma once 
#include "GameObject/MovingObject/MovingObject.h"

class Player;

class Cage : public MovingObject
{
public:
	Cage(float, float);
	virtual void move(const sf::Time&) override;
	void setLiftCage();

private:
	std::pair<sf::IntRect, sf::IntRect> m_cageStatusRect;
	bool m_liftCage;
	float m_cageHeight;
};