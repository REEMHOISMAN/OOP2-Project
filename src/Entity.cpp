#include "Entity.h"

Entity::Entity(sf::Vector2f& position, sf::Texture& texture)
	:GameObject(position,texture)
{
}
//---------------------------------------------------------
void Entity::setEntityPosition(sf::Vector2f& Pos)
{
	sf::Vector2f oldPos = getObjectSprite().getPosition();
	sf::Vector2f newPos = { Pos.x * getObjectSprite().getLocalBounds().getSize().x,0.f};
	getObjectSprite().setPosition(oldPos + newPos);
}
