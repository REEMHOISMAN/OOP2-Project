#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

MovingSaltBomb::MovingSaltBomb(sf::Sprite& sprite,bool rightDirection)
	:MovingObject(sprite),m_rightDirection(rightDirection), 
	m_jumpSpeed(0),m_startegy(std::make_unique<SideToSideStrategy>()),m_toExplode(false){}

void MovingSaltBomb::move(sf::Time time)
{
	m_jumpSpeed = time.asSeconds() * 200;
	activateGravity(0.3);
	auto newPos=m_startegy->move(time, m_rightDirection, getGravity());
	setObjectPosition(newPos + getObjectSprite().getPosition());
}

void MovingSaltBomb::setExplode()
{
	m_toExplode = !m_toExplode;
}

bool MovingSaltBomb::toExplode()
{
	return m_toExplode;
}

bool MovingSaltBomb::isDirectionRight() const
{
	return m_rightDirection;
}

float MovingSaltBomb::getJumpSpeed() const
{
	return m_jumpSpeed ;
}
