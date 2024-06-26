#include "GameObject/MovingObject/MovingObject.h"

MovingObject::MovingObject(sf::Sprite& sprite):
	GameObject(sprite),m_grounded(false),m_blockFromSide(false), m_gravity(0.f)
{
}

void MovingObject::setOnGround(bool val)
{
	m_grounded = val;
}

bool MovingObject::isOnGround()const
{
	return m_grounded;
}

void MovingObject::activateGravity(float gravity)
{
	m_gravity += gravity;
}

float MovingObject::getGravity() const
{
	return m_gravity;
}

void MovingObject::resetGravity() {
	m_gravity = 0;
}

bool MovingObject::isBlockedFromSide() const
{
	return m_blockFromSide;
}

void MovingObject::setBlockedOnSide(bool val)
{
	m_blockFromSide = val;
}
