#pragma once

#include "States/PlayerState/PlayerState.h"

class JumpState:public PlayerState
{
public:
	JumpState(Player& player, Input);
	std::unique_ptr<PlayerState>handleEvent(Input,Player&)override;
	void update(sf::Time)override;
private:
	float m_jumpSpeed;
	float m_rightLeftSpeed;
	float m_gravity;
};