#pragma once
#include "GameObject/MovingObject/MovingObject.h"

class Entity :public MovingObject
{
public:
	Entity(sf::Sprite&);
	bool isHeadDirectionRight() const;
	void setHeadDirection();
	

private:
	bool m_RightDirection;
};