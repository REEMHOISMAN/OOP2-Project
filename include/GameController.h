#pragma once
#include <SFML/Graphics.hpp>
#include "DesignPatterns/States/GameState/InGameState.h"
class GameState;

class GameController
{
public:
	GameController();
	void run();

private:
	sf::RenderWindow m_window;
	GameState* m_state;
	
	InGameState m_inGameState;
};