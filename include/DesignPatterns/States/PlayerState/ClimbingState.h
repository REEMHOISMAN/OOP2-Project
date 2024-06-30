#pragma once

#include "DesignPatterns/States/PlayerState/PlayerState.h"

class ClimbingState:public PlayerState
{
public:
	ClimbingState(const ObjectAnimation type);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&)override;
	virtual void update(sf::Time, Player&)override;
private:
	float m_climbSpeed;
	float m_xSpeed;
};