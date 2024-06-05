#include "GameObject.h"
#include "GameObject.h"
#include "Player.h"

GameObject::GameObject(sf::Sprite& sprite): m_sprite(sprite)
{
}

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

