#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include <vector>

class GameController;
class Button;

class MenuState : public GameState
{
public:
	MenuState(GameController&, GameState&, GameState&, Button&);
	virtual void handleEvent(sf::Event&, sf::RenderWindow&) override;
	virtual void update(sf::Time) override {}
	virtual void render(sf::RenderWindow&) override;

private:
	sf::RectangleShape m_background;
	std::vector<Button>m_buttons;
	Button& m_soundButton;
};