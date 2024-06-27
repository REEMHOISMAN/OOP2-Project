#pragma once 
#include <memory>
#include <SFML/Graphics.hpp>
#include "Macros.h"

class PizzaEnemy;
class Enemy;

class PizzaEnemyState 
{
public:
	PizzaEnemyState(const ObjectAnimation, const sf::Time m_animationTime);
	bool setAnimationFrame(PizzaEnemy& , sf::Time);
	virtual ~PizzaEnemyState() = default;
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&, sf::Time) = 0;
	virtual void update(sf::Time, PizzaEnemy&) = 0;

private:
	Animation m_animation;
	sf::Time m_elapsed;
	sf::Time m_animationTime;
	int m_frame;
};