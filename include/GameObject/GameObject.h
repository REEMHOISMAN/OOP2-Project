#pragma once
#include <SFML/Graphics.hpp>

class GameObject 
{
public:
	GameObject();
	GameObject(sf::Sprite&);
	virtual ~GameObject() = default;
	void setObjectPosition(const sf::Vector2f&);
	virtual void draw(sf::RenderWindow& window)const;
	sf::Sprite getObjectSprite()const;
	const sf::IntRect getTextureRect() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
	void setScale();
	void setObjectSprite(sf::Sprite&);
	void setTextureRect(const sf::IntRect&);
	bool isCollide(const sf::Sprite& sprite);
	void setToErase();
	bool ToErase()const;

private:
	sf::Sprite m_sprite;
	bool m_isCollide;
	bool m_eraseCondition;
};