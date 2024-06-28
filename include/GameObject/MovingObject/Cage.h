#pragma once 
#include "GameObject/MovingObject/MovingObject.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"

class Player;
class Cage : public MovingObject
{
public:
	Cage(float, float);
	virtual void move(sf::Time) override;
	void setLiftCage();

private:
	std::pair<sf::IntRect, sf::IntRect> m_cageStatusRect;
	bool m_liftCage;
};