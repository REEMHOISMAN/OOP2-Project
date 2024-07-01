#include "GameObject/GameObject.h"
#include <iostream> 

/*================== GameObject Constructor =================*/
GameObject::GameObject():m_eraseCondition(false), m_isCollide(false){}

/*================== GameObject Constructor =================*/
GameObject::GameObject(sf::Sprite& sprite) : m_sprite(sprite), m_isCollide{ false }, m_eraseCondition{false} {}

/*================== setObjectPosition =================*/
void GameObject::setObjectPosition(const sf::Vector2f& newPos)
{
	m_sprite.setPosition(newPos);
}

/*================== draw =================*/
void GameObject::draw(sf::RenderWindow& window)const
{
	window.draw(m_sprite);
}

/*================== getObjectSprite =================*/
sf::Sprite GameObject::getObjectSprite()const
{
	return m_sprite;
}

/*================== getTextureRect =================*/
const sf::IntRect GameObject::getTextureRect()const
{
	return m_sprite.getTextureRect();
}

/*================== getGlobalBounds =================*/
const sf::FloatRect GameObject::getGlobalBounds()const
{
	return m_sprite.getGlobalBounds();
}

/*================== getPosition =================*/
const sf::Vector2f GameObject::getPosition()const
{
	return m_sprite.getPosition();
}

/*================== setScale =================*/
void GameObject::setScale()
{
 	m_sprite.scale(-1.f,1.f);
}
/*================== setObjectSprite =================*/
void GameObject::setObjectSprite(sf::Sprite& sprite)
{
	m_sprite = sprite;
}

/*================== setTextureRect =================*/
void GameObject::setTextureRect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
	m_sprite.setOrigin(static_cast<float>(rect.width / 2), static_cast<float>(rect.height / 2));
}
/*================== isCollide =================*/
bool GameObject::isCollide(const sf::Sprite& sprite)
{
	auto rect = sprite.getGlobalBounds();
	auto pos = sprite.getPosition();
	auto pos2 = m_sprite.getPosition();
	m_isCollide = m_sprite.getGlobalBounds().intersects(rect);
	return m_isCollide;
}

/*================== setToErase =================*/
void GameObject::setToErase() 
{
	m_eraseCondition = true;
}
/*================== ToErase =================*/
bool GameObject::ToErase()const
{
	return m_eraseCondition;
}