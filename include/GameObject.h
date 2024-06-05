#pragma once
#include <SFML/Graphics.hpp>
class GameObject 
{
public:
	GameObject(sf::Vector2f& position, sf::Texture& texture);
	void draw(sf::RenderWindow& window);
	sf::Sprite& getObjectSprite();
private:
	sf::Sprite m_sprite;
};