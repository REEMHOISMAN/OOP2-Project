#include "GameObject.h"

GameObject::GameObject(sf::Vector2f& position, sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
}

//---------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//---------------------------------------------------------
sf::Sprite& GameObject::getObjectSprite()
{
	return m_sprite;
}

