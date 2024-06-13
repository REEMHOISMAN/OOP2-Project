#pragma once

#include "States/PlayerState/PlayerState.h"

class DivingState :public PlayerState
{
public:
	DivingState();
	std::unique_ptr<PlayerState>handleEvent(Input, Player&)override;
	void update(sf::Time, Player&)override;
private:
	float m_rightLeftSpeed;
};