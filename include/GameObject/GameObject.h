#pragma once
#include <SFML/Graphics.hpp>

class GameObject 
{
public:
	GameObject();
	GameObject(sf::Sprite&);
	void setObjectPosition(const sf::Vector2f&);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window)const;
	sf::Sprite getObjectSprite()const;
	void setScale();
	void setObjectSprite(sf::Sprite&);
	void setTextureRect(const sf::IntRect&);
	bool isCollide(const sf::Sprite& sprite);
	bool playerIsColide()const;
	void setToErase();
	bool ToErase()const;

private:
	sf::Sprite m_sprite;
	bool m_isCollide;
	bool m_eraseCondition;
};