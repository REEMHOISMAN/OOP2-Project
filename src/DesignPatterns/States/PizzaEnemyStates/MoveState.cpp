#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"
#include "DesignPatterns/States/PizzaEnemyStates/AttackState.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "GameObject/MovingObject/PizzaEnemy.h"

MoveState::MoveState(const ObjectAnimation animation, const sf::Time& frameTimer):
	PizzaEnemyState(animation, frameTimer), m_jumps(0), m_walkTime(sf::seconds(1.5f))
{

}

std::unique_ptr<PizzaEnemyState> MoveState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{	
	if (m_jumps == 2 && m_walkTime.asSeconds() <= 0.75f && pizzaEnemy.isOnGround()) {
  		return std::make_unique<AttackState>(PIZZA_ENEMY_ATTACK, sf::seconds(0.25f));
	}
	
	return nullptr;
}

void MoveState::update(sf::Time deltaTime, PizzaEnemy& pizzaEnemy) 
{

	if (m_walkTime.asSeconds() <= 0.f && !pizzaEnemy.isBlockedFromSide())
	{

		float posX = deltaTime.asSeconds() * 100.f;
		pizzaEnemy.setStrategy(std::make_unique<UpDownStrategy>(posX));
		m_walkTime = sf::seconds(1.5f);
		m_jumps++;
	}
	else
	{
		m_walkTime -= deltaTime;
	}

	if (!pizzaEnemy.isOnGround())
		pizzaEnemy.activateGravity(0.3f);

	else
		pizzaEnemy.resetGravity();

	setAnimationFrame(pizzaEnemy, deltaTime);
	pizzaEnemy.activateStrategy(deltaTime);
	pizzaEnemy.setOnGround(false);
	pizzaEnemy.setBlockedOnSide(false);
}

