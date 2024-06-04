#pragma once
#include "PlayerState.h"

class StandState : public PlayerState
{
public:
	StandState(Player&);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time) override;
};