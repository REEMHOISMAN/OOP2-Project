#pragma once 
#include "DesignPatterns/Strategies/MovingStrategy.h"

class WalkAndJumpStrategy : public MovingStrategy
{
public:
	WalkAndJumpStrategy();
	virtual sf::Vector2f& move(sf::Time, bool, float) override;
	void resetIsJumping();

private:
	sf::Time m_walkTimer;
	bool m_isJumping;
};