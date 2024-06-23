#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player;

class UserInterface
{
public:
	UserInterface();
	void showGameInfo(sf::RenderWindow& window, Player&);
	void setStaticObjectInfo(std::string& str, float factorX, float factorY);

private:
	void setSpriteInfo(sf::Sprite& sprite, float factorX, float factorY);
	void setSpriteInfo(std::string& str, float factorX, float factorY);
	sf::RectangleShape m_userInterface;
};