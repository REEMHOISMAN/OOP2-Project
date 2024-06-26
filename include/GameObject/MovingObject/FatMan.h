#pragma once 
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "GameObject/MovingObject/Cage.h"

class FatMan:public Enemy
{
public:
	FatMan(sf::Sprite&, std::unique_ptr<MovingStrategy>,const float);
	virtual void move(sf::Time)override;
private:
	float m_cageX;
};