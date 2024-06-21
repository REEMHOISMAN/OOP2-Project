#pragma once
#include "GameObject/MovingObject/MovingObject.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"

class MovingSaltBomb :public MovingObject 
{
public:
	MovingSaltBomb(sf::Sprite&,bool);
	virtual void move(sf::Time)override;
	void setExplode();
	bool toExplode();
	bool isDirectionRight()const;
	float getJumpSpeed()const;
private:
	float m_jumpSpeed;
	
	bool m_rightDirection;
	bool m_toExplode;
	std::unique_ptr<MovingStrategy> m_startegy;
};