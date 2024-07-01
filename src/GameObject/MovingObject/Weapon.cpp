#include "GameObject/MovingObject/Weapon.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

/*================== Weapon Constructor =================*/
Weapon::Weapon(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, bool right): 
	MovingObject(sprite), m_moveStrategy(std::move(strategy)), m_rightDirection(right){}

/*================== move =================*/
void Weapon::move(const sf::Time& elapsedTime)
{
	auto newPos = m_moveStrategy->move(elapsedTime, m_rightDirection, getGravity());
	setObjectPosition(getPosition() + newPos );
}

/*================== setStrategy =================*/
void Weapon::setStrategy(std::unique_ptr<MovingStrategy> strategy)
{
	m_moveStrategy = std::move(strategy);
}
