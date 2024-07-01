#pragma once

#include "DesignPatterns/States/PlayerState/PlayerState.h"

class DivingState :public PlayerState
{
public:
	DivingState(const ObjectAnimation animation);
	std::unique_ptr<PlayerState>handleEvent(Input, Player&)override;
	void update(sf::Time, Player&)override;
private:
	float m_rightLeftSpeed;
	bool m_scaled;
};