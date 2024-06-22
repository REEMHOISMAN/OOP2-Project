#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"

class CheesedState : public PlayerState
{
public:
	CheesedState(const ObjectAnimation animation);
	std::unique_ptr<PlayerState>handleEvent(Input, Player&)override;
	void update(sf::Time, Player&)override;

private:
	int m_spaceCounter;
	bool m_pressingOnSpace;
	bool m_wasPressedOnSpace;
};