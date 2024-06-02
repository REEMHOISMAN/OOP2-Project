#pragma once
#include <SFML/Graphics.hpp>

class GameController
{
public:
	GameController();
	void run();

private:
	sf::RenderWindow m_window;
};