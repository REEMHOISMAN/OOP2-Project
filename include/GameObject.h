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
	void setScale(float x, float y);
	void setOrigin(const sf::Vector2f& origin);
private:
	sf::Sprite m_sprite;
};