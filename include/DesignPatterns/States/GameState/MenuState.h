#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include "Button.h"
#include <vector>

class GameController;

class MenuState : public GameState
{
public:
	MenuState(GameController&, GameState&);
	virtual void handleEvent(sf::Event&, sf::RenderWindow&) override;
	virtual void update(sf::Time) override {}
	virtual void render(sf::RenderWindow&) override;

private:
	sf::RectangleShape m_background;
	std::vector<Button>m_buttons;
};