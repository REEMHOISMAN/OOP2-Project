#include "Entity.h"

Entity::Entity(sf::Sprite& sprite):
	GameObject(sprite), m_RightDirection(false), m_grounded(false), 
	m_blockFromSide(false), m_gravity(0){}

bool Entity::isHeadDirectionRight() const
{
	return m_RightDirection;
}

void Entity::setHeadDirection()
{
	m_RightDirection = !m_RightDirection;
}

void Entity::setOnGround(bool val)
{
	m_grounded = val;
}

bool Entity::isOnGround()const
{
	return m_grounded;
}

void Entity::activateGravity(float gravity)
{
	m_gravity += gravity;
}

float Entity::getGravity() const
{
	return m_gravity;
}

void Entity::resetGravity() {
	m_gravity = 0;
}

bool Entity::isBlockedFromSide() const
{
	return m_blockFromSide;
}

void Entity::setBlockedOnSide(bool val)
{
	m_blockFromSide = val;
}
