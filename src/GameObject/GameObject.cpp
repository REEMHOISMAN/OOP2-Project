#include "GameObject/GameObject.h"
#include <iostream> 

GameObject::GameObject():m_eraseCondition(false), m_isCollide(false){}

GameObject::GameObject(sf::Sprite& sprite) : m_sprite(sprite), m_isCollide{ false }, m_eraseCondition{false} {}

void GameObject::setObjectPosition(const sf::Vector2f& newPos)
{
	m_sprite.setPosition(newPos);
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
void GameObject::setObjectSprite(sf::Sprite& sprite)
{
	m_sprite = sprite;
}

//---------------------------------------------------------
void GameObject::setTextureRect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
	m_sprite.setOrigin(static_cast<float>(rect.width / 2), static_cast<float>(rect.height / 2));
}

bool GameObject::isCollide(const sf::Sprite& sprite)
{
	auto rect = sprite.getGlobalBounds();
	auto pos = sprite.getPosition();
	auto pos2 = m_sprite.getPosition();
	m_isCollide = m_sprite.getGlobalBounds().intersects(rect);
	return m_isCollide;
}

bool GameObject::playerIsColide() const
{
	return m_isCollide;
}

void GameObject::setToErase() 
{
	m_eraseCondition = true;
}
bool GameObject::ToErase()const
{
	return m_eraseCondition;
}