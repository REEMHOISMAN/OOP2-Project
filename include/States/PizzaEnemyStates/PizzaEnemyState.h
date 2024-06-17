#pragma once 
#include "PizzaEnemy.h"

class PizzaEnemyState 
{
public:
	PizzaEnemyState()=default;
	virtual ~PizzaEnemyState() = default;
	virtual std::unique_ptr<PizzaEnemyState> handleTime(float, PizzaEnemy&) = 0;
	virtual void update(sf::Time, PizzaEnemy&) = 0;
};