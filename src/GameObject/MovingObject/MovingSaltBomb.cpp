#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

MovingSaltBomb::MovingSaltBomb(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy,bool rightDirection)
	:Weapon(sprite,std::move(strategy), rightDirection), m_toExplode(false) 
{
	/*activateGravity(0.2f);*/
}

void MovingSaltBomb::setExplode()
{
	m_toExplode = !m_toExplode;
}

bool MovingSaltBomb::toExplode()
{
	return m_toExplode;
}

void MovingSaltBomb::move(sf::Time time)
{
	if (!m_toExplode)
		activateGravity(0.2f);
	else
		activateGravity(0.3f);
	Weapon::move(time);
}
