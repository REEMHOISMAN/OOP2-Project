#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

MovingSaltBomb::MovingSaltBomb(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy,bool rightDirection,float Jumpspeed)
	:Weapon(sprite,std::move(strategy), rightDirection), m_jumpSpeed(Jumpspeed), m_toExplode(false) 
{
	activateGravity(0.1f);
}

void MovingSaltBomb::setExplode()
{
	m_toExplode = !m_toExplode;
}

bool MovingSaltBomb::toExplode()
{
	return m_toExplode;
}
float MovingSaltBomb::getJumpSpeed() const
{
	return m_jumpSpeed ;
}
