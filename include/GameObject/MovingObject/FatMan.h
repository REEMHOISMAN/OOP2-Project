#pragma once 
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "GameObject/MovingObject/Cage.h"

class Level;

class FatMan:public Enemy
{
public:
	FatMan(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation, Level&);
	virtual void move(const sf::Time&)override;
	void setIsHappy();
	void setIsAngry();
	bool isHappy() const;
	int getTotalPizzas()const;

private:
	void loadAnimationFrame(sf::Time);

	static bool m_register;
	Animation m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
	float m_startPosX;
	bool m_isHappy;
	bool m_isAngry;
	Level& m_level;
};