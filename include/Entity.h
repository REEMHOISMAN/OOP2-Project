#pragma once
#include "GameObject.h"

class Entity :public GameObject
{
public:
	Entity(sf::Sprite&);
	virtual void move(sf::Time) = 0;
	bool isHeadDirectionRight() const;
	void setHeadDirection();
	void setOnGround(bool val);
	bool isOnGround() const;
	void activateGravity(float);
	float getGravity() const;

private:
	bool m_RightDirection;
	bool m_grounded;
	float m_gravity;
};