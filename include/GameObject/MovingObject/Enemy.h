#pragma once
#include "GameObject/MovingObject/Entity.h"
#include "vector"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>

using Animation = std::vector<sf::IntRect>;

class Enemy : public Entity
{
public:
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&);

protected:
	std::unique_ptr<MovingStrategy> getStrategy();

	void setStrategy(std::unique_ptr<MovingStrategy>);

private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
}