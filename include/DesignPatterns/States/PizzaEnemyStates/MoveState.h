#pragma once
#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"

class MoveState :public PizzaEnemyState
{
public:
	MoveState(const ObjectAnimation, const sf::Time& frameTimer);
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&, sf::Time deltaTime)override;
	virtual void update(sf::Time, PizzaEnemy&)override;
private:
	int m_jumps;
	sf::Time m_walkTime;
};