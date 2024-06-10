#pragma once

#include "States/PlayerState/PlayerState.h"

class DivingState :public PlayerState
{
public:
	DivingState(Player& player, Input);
	std::unique_ptr<PlayerState>handleEvent(Input, Player&)override;
	void update(sf::Time)override;
private:
	float m_rightLeftSpeed;
};