#pragma once
#include "GameObject/MovingObject/Weapon.h"
#include "Macros.h"

class MovingStrategy;

class MovingSaltBomb :public Weapon 
{
public:
	MovingSaltBomb(sf::Sprite&, std::unique_ptr<MovingStrategy> ,bool);
	virtual void move(const sf::Time&)override;
	void setExplode();
	bool isExplode()const;
	void setJumps();
	int getJumps()const;
	
private:
	void updateExplodeAnimation(sf::Time);
	bool m_toExplode;
	std::unique_ptr<MovingStrategy> m_startegy;
	Animation m_explodeAnimation;
	sf::Time m_elapsed;
	int m_jumps;
	int m_frame;
};