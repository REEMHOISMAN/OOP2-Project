#pragma once
#include "GameObject/MovingObject/MovingObject.h"
#include <memory>

class MovingStrategy;

class Weapon : public MovingObject
{
public:
	Weapon(sf::Sprite&, std::unique_ptr<MovingStrategy>, bool);
	void setStrategy(std::unique_ptr<MovingStrategy> strategy);
	void move(const sf::Time&)override;

private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
	bool m_rightDirection;
};