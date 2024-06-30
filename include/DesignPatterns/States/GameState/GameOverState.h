#pragma once 
#include "DesignPatterns/States/GameState/GameState.h"
#include "Button.h"

class MenuState;
class GameController;

class GameOverState :public GameOverState 
{
public:
	GameOverState(GameController& controller, GameState& state)
	virtual void handleEvent(sf::Event&, sf::RenderWindow& window)override;
	virtual void update(sf::Time)override;
	virtual void render(sf::RenderWindow& window)override;
private:
	Button& m_button;


};