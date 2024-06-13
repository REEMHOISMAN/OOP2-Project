#pragma once
#include "Entity.h"
#include "vector"
#include "Strategies/MovingStrategy.h"
#include <memory>

using Animation = std::vector<sf::IntRect>;

class Enemy : public Entity
{
public:
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&);
	virtual void move(sf::Time) override;

private:
	void activateGravity();
	void loadAnimation(sf::Time);
	Animation m_animation;
	std::unique_ptr<MovingStrategy> m_moveStrategy;
	
	float m_gravity;
	int m_animationIndex;
	sf::Time m_elapsed;
};