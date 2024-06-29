#pragma once 
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "GameObject/MovingObject/Cage.h"

class FatMan:public Enemy
{
public:
	FatMan(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation, int);
	virtual void move(sf::Time)override;
	void setIsHappy();
	void setIsAngry();
	bool isHappy() const;
	int getTotalPizzas()const;

private:
	void loadAnimationFrame(sf::Time);

	static bool m_register;
	Animation m_animation;
	int m_animationIndex;
	int m_totalPizzas;
	sf::Time m_elapsed;
	float m_startPosX;
	bool m_isHappy;
	bool m_isAngry;
};