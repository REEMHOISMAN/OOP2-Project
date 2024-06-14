#pragma once
#include <SFML/Graphics.hpp>

class GameObject 
{
public:
	GameObject(sf::Sprite&);
	void setObjectPosition(const sf::Vector2f&);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window)const;
	sf::Sprite getObjectSprite()const;
	void setScale();
	void setOrigin(const sf::Vector2f& origin);
	void setTextureRect(const sf::IntRect&);
	bool isCollide(const sf::Sprite& sprite) const;
	void setCollidenes(bool colide);
	bool playerIsColide()const;

private:
	sf::Sprite m_sprite;
	bool m_isCollide;
};