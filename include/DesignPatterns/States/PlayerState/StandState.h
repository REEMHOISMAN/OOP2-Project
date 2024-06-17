#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"

class StandState : public PlayerState
{
public:
	StandState(const ObjectAnimation animation);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time, Player&) override;
};