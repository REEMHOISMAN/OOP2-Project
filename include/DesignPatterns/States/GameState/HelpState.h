#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include "Button.h"

class GameController;

class HelpState : public GameState
{
public:
	HelpState(GameController& controller, GameState& state);
	virtual void handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) {};
	virtual void render(sf::RenderWindow& window) override;
	void setBackground(const std::string);

private:
	sf::RectangleShape m_background;
	Button m_goBackButton;
};