#include "Strategies/JumpingStrategy.h"

sf::Vector2f& JumpingStrategy::move(sf::Time deltaTime, bool rightDirection, float gravity)
{
	sf::Vector2f pos;
	auto jumpSpeed= deltaTime.asSeconds() * 600.f;
	return pos = { 0,-jumpSpeed + gravity };
}
