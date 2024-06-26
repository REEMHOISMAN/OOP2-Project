#include "GameObject/MovingObject/Cage.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
Cage::Cage(sf::Sprite& sprite, std::unique_ptr<UpDownStrategy> strategy):
	MovingObject(sprite),m_strategy(std::move(strategy)), m_liftCage(false){}

void Cage::move(sf::Time delta)
{
	if (m_liftCage)
	{
		m_strategy->move(delta, false, 0.f);
	}
}
