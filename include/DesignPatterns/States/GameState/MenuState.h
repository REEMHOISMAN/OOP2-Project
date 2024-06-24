#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include "Button.h"
#include <vector>
class MenuState : public GameState
{
public:
	MenuState();
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow&) override { return nullptr; }
	virtual void update(sf::Time) override {}
	virtual void render(sf::RenderWindow&) override {}

private:
	sf::RectangleShape m_backGround;
	std::vector<Button>m_buttons;
};