#pragma once
#include "GameObject/GameObject.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"

class MovingObject:public GameObject 
{
public:
	MovingObject(sf::Sprite&);
	virtual void move(sf::Time)=0;
	void setOnGround(bool val);
	bool isOnGround() const;
	void activateGravity(float);
	float getGravity() const;
	void resetGravity();
	bool isBlockedFromSide() const;
	void setBlockedOnSide(bool val);


private:
	bool m_grounded;
	bool m_blockFromSide;
	float m_gravity;

};