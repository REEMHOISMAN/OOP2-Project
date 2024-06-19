#pragma once
#include "PizzaEnemyState.h"

class AttackState : public PizzaEnemyState
{
public:
	AttackState() = default;
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&, float&, sf::Time);
	virtual void update(sf::Time, PizzaEnemy&);
};