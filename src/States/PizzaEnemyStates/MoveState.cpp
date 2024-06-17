#include "States/PizzaEnemyStates/MoveState.h"
#include "Strategies/UpDownStrategy.h"
#include "PizzaEnemy.h"
#include "Enemy.h"

MoveState::MoveState():
	m_jumps(0)
{
}

std::unique_ptr<PizzaEnemyState> MoveState::handleTime(PizzaEnemy& pizzaEnemy,float& walkTime,sf::Time deltaTime)
{
	if (walkTime <= 0.f) 
	{

		float posX = deltaTime.asSeconds() * 100.f;
		pizzaEnemy.loadStrategy(std::move(std::make_unique< UpDownStrategy>(posX)));
		walkTime = 2.0f;
		
	}
	if (m_jumps == 2 && walkTime <= 1.f) {
		/*pizzaEnemy.loadAnimation(PIZZA_ENEMY_ATTACK);
		m_jumps = 0;*/
		//return std::make_unique<AttackState>();
	}
	
	return nullptr;
}

void MoveState::update(sf::Time deltaTime, Enemy& pizzaEnemy) 
{
	pizzaEnemy.move(deltaTime);
}

