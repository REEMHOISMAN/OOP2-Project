#pragma once
#include "States/PlayerState/PlayerState.h"

class WalkState : public PlayerState
{
public:
	WalkState(const ObjectAnimation);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time, Player&) override;

private:
	float m_walkTimer;
};