#pragma once
#include "States/PlayerState/PlayerState.h"

class RunState : public PlayerState
{
public:
	RunState();
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time, Player&) override;

private:
	float m_acceleration;
};