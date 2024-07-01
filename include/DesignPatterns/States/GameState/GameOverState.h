#pragma once 
#include "DesignPatterns/States/GameState/GameState.h"
#include "Button.h"

class GameController;
class InGameState;

class GameOverState :public GameState 
{
public:
	GameOverState(GameController& controller, GameState& menu , InGameState& inGame);
	virtual void handleEvent(sf::Event&, sf::RenderWindow& window)override;
	virtual void update(sf::Time)override {}
	virtual void render(sf::RenderWindow& window)override;

private:
	sf::RectangleShape m_background;
	Button m_button;
	InGameState& m_inGame;
};