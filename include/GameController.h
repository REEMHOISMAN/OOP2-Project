#pragma once
#include <SFML/Graphics.hpp>
#include "InGameState.h"
class GameStates;

class GameController
{
public:
	GameController();
	void run();

private:
	sf::RenderWindow m_window;
	GameStates* m_state;
	InGameState m_inGameState;
};