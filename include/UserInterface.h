#pragma once
#include <SFML/Graphics.hpp>

class Player;

class UserInterface
{
public:
	UserInterface();
	void showGameInfo(sf::RenderWindow& window, Player&);

private:
	sf::RectangleShape m_userInterface;
};