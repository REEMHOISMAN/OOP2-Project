#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"

class BombState : public PlayerState
{
public:
	BombState(const ObjectAnimation animation);
	std::unique_ptr<PlayerState>handleEvent(Input, Player&)override;
	void update(sf::Time, Player&)override;
private:
	sf::Sprite m_saltBomb;
};