#pragma once
#include "GameObject.h"

class Entity :public GameObject
{
public:
	Entity(sf::Sprite&);
	bool isHeadDirectionRight() const;
	void setHeadDirection();
	virtual void move(sf::Time) = 0;

private:
	bool m_RightDirection;
};