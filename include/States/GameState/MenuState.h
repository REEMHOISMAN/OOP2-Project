#pragma once
#include "States/GameState/GameState.h"

class MenuState : public GameState
{
public:
	MenuState() = default; //just for now..
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow&) override { return nullptr; }
	virtual void update(sf::Time) override {}
	virtual void render(sf::RenderWindow&) override {}

private:
	// here we need to think
};