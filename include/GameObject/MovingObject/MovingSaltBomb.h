#pragma once
#include "GameObject/MovingObject/Weapon.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"

class MovingSaltBomb :public Weapon 
{
public:
	MovingSaltBomb(sf::Sprite&, std::unique_ptr<MovingStrategy> ,bool);
	void setExplode();
	bool toExplode();
	virtual void move(sf::Time)override;
private:
	bool m_toExplode;
	std::unique_ptr<MovingStrategy> m_startegy;
};