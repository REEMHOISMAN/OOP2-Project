#pragma once 

#include "GameObject/MovingObject/Enemy.h"

class BasicEnemy :public Enemy 
{
public:
	BasicEnemy(sf::Sprite&,std::unique_ptr<MovingStrategy>,Animation&);
	virtual void move(const sf::Time&)override;
	
	
private:
	void loadAnimationFrame(sf::Time);
	static bool m_register;
	Animation m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
};