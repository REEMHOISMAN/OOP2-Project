#pragma once 
#include "GameObject/MovingObject/Weapon.h"

class CheeseBullet :public Weapon 
{
public:
	CheeseBullet(sf::Sprite&,std::unique_ptr<MovingStrategy>,bool);
	//virtual void move(sf::Time)override;
};