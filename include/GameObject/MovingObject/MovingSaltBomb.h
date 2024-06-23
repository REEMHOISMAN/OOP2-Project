#pragma once
#include "GameObject/MovingObject/Weapon.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "Macros.h"

class MovingSaltBomb :public Weapon 
{
public:
	MovingSaltBomb(sf::Sprite&, std::unique_ptr<MovingStrategy> ,bool);
	void setExplode();
	bool isExplode();
	void setJumps();
	int getJumps()const;
	virtual void move(sf::Time)override;
	
private:
	void updateExplodeAnimation(sf::Time);
	bool m_toExplode;
	std::unique_ptr<MovingStrategy> m_startegy;
	Animation m_explodeAnimation;
	sf::Time m_elapsed;
	int m_jumps;
	int m_frame;
};