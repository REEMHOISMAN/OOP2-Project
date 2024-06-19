#pragma once
#include "PizzaEnemyState.h"

class AttackState : public PizzaEnemyState
{
public:
	AttackState(const ObjectAnimation);
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&, sf::Time);
	virtual void update(sf::Time, PizzaEnemy&);

private:
	bool m_generateCheese;
	sf::Sprite m_cheese;
};