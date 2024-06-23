#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player;

class UserInterface
{
public:
	UserInterface();
	void showGameInfo(sf::RenderWindow& window, Player&);
	void setStaticObjectInfo(Player& ,sf::RenderWindow& window,std::string str,std::string toStr,float factorX, float factorY);

private:
	sf::RectangleShape m_userInterface;
};