#pragma once
#include "MovingObject.h"

class Entity :public MovingObject
{
public:
	Entity(sf::Sprite&);
	virtual void move(sf::Time) = 0;
	bool isHeadDirectionRight() const;
	void setHeadDirection();
	

private:
	bool m_RightDirection;
};