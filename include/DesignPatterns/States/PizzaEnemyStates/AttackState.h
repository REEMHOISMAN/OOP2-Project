#pragma once
#include "PizzaEnemyState.h"

class AttackState : public PizzaEnemyState
{
public:
	AttackState(const ObjectAnimation, const sf::Time);
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&, sf::Time);
	virtual void update(sf::Time, PizzaEnemy&);

private:
	bool m_generateCheese;
	sf::Sprite m_cheese;
};