#include "GameObject/MovingObject/Entity.h"

Entity::Entity(sf::Sprite& sprite):
	MovingObject(sprite), m_RightDirection(false){}

bool Entity::isHeadDirectionRight() const
{
	return m_RightDirection;
}

void Entity::setHeadDirection(bool val)
{
	m_RightDirection = val;
}


