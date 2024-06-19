#pragma once
#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"

class MoveState :public PizzaEnemyState
{
public:
	MoveState(const ObjectAnimation);
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&,float&, sf::Time deltaTime)override;
	virtual void update(sf::Time, PizzaEnemy&)override;
private:
	int m_jumps;
};