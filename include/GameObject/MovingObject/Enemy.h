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