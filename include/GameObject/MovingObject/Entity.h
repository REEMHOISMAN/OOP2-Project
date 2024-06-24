#pragma once
#include "GameObject/MovingObject/MovingObject.h"

class Entity :public MovingObject
{
public:
	Entity() : m_RightDirection(false) {}
	Entity(sf::Sprite&);
	bool isHeadDirectionRight() const;
	void setHeadDirection(bool);
	

private:
	bool m_RightDirection;
};