#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void draw(sf::RenderWindow&)const;

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};