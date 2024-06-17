#pragma once
#include "Entity.h"
#include "vector"
#include "Strategies/MovingStrategy.h"
#include "ResourceManager.h"
#include <memory>

using Animation = std::vector<sf::IntRect>;

class Enemy : public Entity
{
public:
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&);
	virtual void move(sf::Time) override;
	void loadStrategy(std::unique_ptr<MovingStrategy> strategy);
	void loadAnimation(const ObjectAnimation&);
	void loadNewFrame(sf::Time);


private:
	Animation m_animation;
	std::unique_ptr<MovingStrategy> m_moveStrategy;
	
	int m_animationIndex;
	sf::Time m_elapsed;
};