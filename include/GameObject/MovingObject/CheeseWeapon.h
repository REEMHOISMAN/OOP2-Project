#pragma once 
#include "GameObject/MovingObject/Weapon.h"

class CheeseWeapon :public Weapon 
{
public:
	CheeseWeapon(sf::Sprite&,std::unique_ptr<MovingStrategy>,bool);
	virtual void move(sf::Time)override;
private:
	bool m_rightDirection;
};