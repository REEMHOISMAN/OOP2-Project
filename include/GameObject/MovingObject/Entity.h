#pragma once
#include "GameObject/MovingObject/MovingObject.h"

class Entity :public MovingObject
{
public:
	Entity() = default;
	Entity(sf::Sprite&);
	//virtual void move(sf::Time) = 0;
	bool isHeadDirectionRight() const;
	void setHeadDirection(bool);
	

private:
	bool m_RightDirection;
};