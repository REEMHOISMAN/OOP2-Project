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
void GameObject::setScale(float x,float y)
{
	//m_sprite.scale(-1.f, 1.f);
	m_sprite.scale(x,y);
}
//---------------------------------------------------------
void GameObject::setOrigin(const sf::Vector2f& origin)
{
	m_sprite.setOrigin(origin);
}

