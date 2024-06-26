#pragma once 
#include "GameObject/MovingObject/MovingObject.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"

class Cage : public MovingObject
{
public:
	Cage(sf::Sprite&, std::unique_ptr<UpDownStrategy>);
	virtual void move(sf::Time) override;

private:
	std::unique_ptr<UpDownStrategy> m_strategy;
	bool m_liftCage;
};