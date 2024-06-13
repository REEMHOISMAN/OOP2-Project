#pragma once
#include "Entity.h"
#include "vector"
#include "Strategies/MovingStrategy.h"
#include <memory>

using Animation = std::vector<sf::IntRect>
;
class Enemy : public Entity
{
public:
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&);

private:
	Animation m_animation;
	std::unique_ptr<MovingStrategy> m_moveStrategy;
};