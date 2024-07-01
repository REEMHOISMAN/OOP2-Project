#include "GameObject/MovingObject/MovingObject.h"

/*================== MovingObject Constructor =================*/
MovingObject::MovingObject():m_blockFromSide(false), m_gravity(0.f), m_grounded(false)
{
}

/*================== MovingObject Constructor =================*/
MovingObject::MovingObject(sf::Sprite& sprite):
	GameObject(sprite),m_grounded(false),m_blockFromSide(false), m_gravity(0.f)
{
}

/*================== setOnGround =================*/
void MovingObject::setOnGround(bool val)
{
	m_grounded = val;
}

/*================== isOnGround =================*/
bool MovingObject::isOnGround()const
{
	return m_grounded;
}

/*================== activateGravity =================*/
void MovingObject::activateGravity(float gravity)
{
	m_gravity += gravity;
}

/*================== getGravity =================*/
float MovingObject::getGravity() const
{
	return m_gravity;
}

/*================== resetGravity =================*/
void MovingObject::resetGravity() {
	m_gravity = 0;
}

/*================== isBlockedFromSide =================*/
bool MovingObject::isBlockedFromSide() const
{
	return m_blockFromSide;
}

/*================== setBlockedOnSide =================*/
void MovingObject::setBlockedOnSide(bool val)
{
	m_blockFromSide = val;
}
