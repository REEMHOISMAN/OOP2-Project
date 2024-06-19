#pragma once 

#include "Enemy.h"

class BasicEnemy :public Enemy 
{
public:
	BasicEnemy(sf::Sprite&,std::unique_ptr<MovingStrategy>,Animation&);
	virtual void move(sf::Time)override;
	
	
private:
	void loadAnimationFrame(sf::Time);
	Animation m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
};