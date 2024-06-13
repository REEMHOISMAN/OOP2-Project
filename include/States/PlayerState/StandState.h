#pragma once
#include "States/PlayerState/PlayerState.h"

class StandState : public PlayerState
{
public:
	StandState() = default;
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time, Player&) override;
};