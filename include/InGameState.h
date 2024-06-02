#pragma once
#include <GameState.h>
#include "Player.h"

class InGameState : public GameState
{
public:
	InGameState() = default; //just for now..
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;

private:
	Player m_player;
};