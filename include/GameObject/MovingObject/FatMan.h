#pragma once 
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "GameObject/MovingObject/Cage.h"

class FatMan:public Enemy
{
public:
	FatMan(sf::Sprite&, std::unique_ptr<MovingStrategy>);
	virtual void move(sf::Time)override;
private:
	static bool m_register;
	//float m_cageX;
};