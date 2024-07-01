#include "GameObject/MovingObject/Entity.h"

/*================== Entity Constructor =================*/
Entity::Entity(sf::Sprite& sprite):
	MovingObject(sprite), m_RightDirection(false){}

/*================== isHeadDirectionRight =================*/
bool Entity::isHeadDirectionRight() const
{
	return m_RightDirection;
}

/*================== setHeadDirection =================*/
void Entity::setHeadDirection(bool val)
{
	m_RightDirection = val;
}


