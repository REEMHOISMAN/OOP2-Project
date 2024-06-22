#include "GameObject/MovingObject/Weapon.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

Weapon::Weapon(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, bool right): 
	MovingObject(sprite), m_moveStrategy(std::move(strategy)), m_rightDirection(right){}

void Weapon::move(sf::Time elapsedTime)
{
	auto newPos = m_moveStrategy->move(elapsedTime, m_rightDirection, getGravity());
	setObjectPosition(getObjectSprite().getPosition() + newPos );
}
