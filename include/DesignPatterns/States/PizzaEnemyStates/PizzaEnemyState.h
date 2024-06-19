#pragma once 
#include <memory>
#include <SFML/Graphics.hpp>
#include "Macros.h"

class PizzaEnemy;
class Enemy;

class PizzaEnemyState 
{
public:
	PizzaEnemyState(const ObjectAnimation);
	void setAnimationFrame(PizzaEnemy& , sf::Time);
	virtual ~PizzaEnemyState() = default;
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&,float&, sf::Time ) = 0;
	virtual void update(sf::Time, PizzaEnemy&) = 0;

private:
	Animation m_animation;
	sf::Time m_elapsed;
	int m_frame;
};