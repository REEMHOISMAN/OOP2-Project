#include "GameObject.h"
#include "GameObject.h"
#include <iostream> 

GameObject::GameObject(sf::Sprite& sprite) : m_sprite(sprite), m_isCollide{false} {}

void GameObject::setObjectPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
}

//---------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)const
{
	window.draw(m_sprite);
	//window.display();
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

bool GameObject::isCollide(const sf::Sprite& sprite) const
{
	auto rect = sprite.getGlobalBounds();
	auto pos = sprite.getPosition();
	auto pos2 = m_sprite.getPosition();
	return m_sprite.getGlobalBounds().intersects(rect);
}

void GameObject::setCollidenes(bool colide)
{
	m_isCollide = colide;
}

bool GameObject::getColideData() const
{
	return m_isCollide;
}
