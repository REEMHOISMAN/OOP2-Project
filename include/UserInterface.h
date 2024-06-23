#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player;

class UserInterface
{
public:
	UserInterface();
	void showGameInfo(sf::RenderWindow& window, Player&);

private:
	void drawSpriteInfo(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scale);
	void drawInfo(sf::RenderWindow& window, const sf::Vector2f& pos, int val);
	void drawHeartSprites(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scaleFactor, int);
	sf::RectangleShape m_userInterface;
};