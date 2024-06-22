#pragma once
#include "GameObject/MovingObject/MovingObject.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include <memory>

class Weapon : public MovingObject
{
public:
	Weapon(sf::Sprite&, std::unique_ptr<MovingStrategy>, bool);
	void move(sf::Time)override;

private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
	bool m_rightDirection;
};