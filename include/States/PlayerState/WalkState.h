#pragma once
#include "States/PlayerState/PlayerState.h"

class WalkState : public PlayerState
{
public:
	WalkState(Player&, Input);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time) override;

private:
	float m_walkTimer;
};