#include "GameObject.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream> 

GameObject::GameObject(sf::Sprite& sprite): m_sprite(sprite){}

void GameObject::setObjectPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
}

//---------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)const
{
	window.draw(m_sprite);
}
//---------------------------------------------------------
sf::Sprite GameObject::getObjectSprite()const
{
	return m_sprite;
}
//---------------------------------------------------------
void GameObject::setScale()
{
	m_sprite.scale(-1.f,1.f);
}
//---------------------------------------------------------
void GameObject::setOrigin(const sf::Vector2f& origin)
{
	m_sprite.setOrigin(origin);
}

//---------------------------------------------------------
void GameObject::setTextureRect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
}

bool GameObject::isCollide(const sf::Sprite& sprite, sf::FloatRect& intersect) const
{
	auto rect = sprite.getGlobalBounds();
	if (m_sprite.getGlobalBounds().intersects(rect, intersect))
	{
		return true;
	}
	return false;
}
