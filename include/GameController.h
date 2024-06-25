#pragma once
#include <SFML/Graphics.hpp>
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/States/GameState/HelpState.h"

class GameState;

class GameController
{
public:
	GameController();
	void changeState(GameState&);
	void run();

private:
	sf::RenderWindow m_window;
	
	GameState* m_state;
	InGameState m_inGameState;
	MenuState m_menuState;
	HelpState m_helpState;
};