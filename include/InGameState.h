#pragma once
#include <GameState.h>

class InGameState : public GameState
{
public:
	InGameState() = default; //just for now..
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;

private:
	// will hold entities, Platyer, and all game objects
};