#pragma once

#include "States/PlayerState/PlayerState.h"

class JumpState:public PlayerState
{
public:
	JumpState(const ObjectAnimation);
	std::unique_ptr<PlayerState>handleEvent(Input,Player&)override;
	void update(sf::Time, Player&)override;

private:
	float m_jumpSpeed;
	float m_rightLeftSpeed;
	float m_jumpTimer;
};