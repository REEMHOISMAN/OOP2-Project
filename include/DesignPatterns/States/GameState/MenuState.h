#pragma once
#include "DesignPatterns/States/GameState/GameState.h"

class MenuState : public GameState
{
public:
	MenuState();
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow&) override { return nullptr; }
	virtual void update(sf::Time) override {}
	virtual void render(sf::RenderWindow&) override {}

private:
	sf::RectangleShape m_backGround;

};