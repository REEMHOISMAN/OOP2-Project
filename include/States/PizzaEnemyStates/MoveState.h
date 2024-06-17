#pragma once
#include "States/PizzaEnemyStates/PizzaEnemyState.h"

class MoveState :public PizzaEnemyState
{
public:
	MoveState();
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&,float&, sf::Time deltaTime)override;
	virtual void update(sf::Time, Enemy&)override;
private:
	int m_jumps;
};