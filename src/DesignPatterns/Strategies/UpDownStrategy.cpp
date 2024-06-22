#include "DesignPatterns/Strategies/UpDownStrategy.h"

UpDownStrategy::UpDownStrategy(float x): m_posX(x)
{
}

sf::Vector2f& UpDownStrategy::move(sf::Time deltaTime, bool rightDirection, float gravity)
{
	sf::Vector2f pos;
	auto jumpSpeed = -deltaTime.asSeconds() * 600.f;
	return pos = {((rightDirection) ? m_posX: -m_posX), jumpSpeed+=gravity};
	
}
