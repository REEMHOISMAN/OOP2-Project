#pragma once 
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "GameObject/MovingObject/Cage.h"

class FatMan:public Enemy
{
public:
	FatMan(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation);
	virtual void move(sf::Time)override;
private:
	void loadAnimationFrame(sf::Time);

	static bool m_register;
	Animation m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
	float m_startPosX;
};