#include "GameObject/MovingObject/PizzaEnemy.h"
#include "Factories/EnemyFactory.h"
#include "Strategies/UpDownStrategy.h"
#include "States/PizzaEnemyStates/MoveState.h"

bool PizzaEnemy::m_register = EnemyFactory::registerEnemy(PIZZA_ENEMY_MOVE,
	[](auto& sprite, auto&& strategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<PizzaEnemy>(sprite, std::move(strategy), animation); });

//--------------------------------------------------------
PizzaEnemy::PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
	: Enemy(sprite, std::move(strategy), animation),m_WalkTimer(2.f),m_jumps(0), m_state(std::move(std::make_unique< MoveState>())) {}

//--------------------------------------------------------
void PizzaEnemy::move(sf::Time deltaTime)
{
	m_WalkTimer -= deltaTime.asSeconds();

	auto state = m_state->handleTime(*this, m_WalkTimer, deltaTime);
	if (state) m_state = std::move(state);
	m_state->update(deltaTime, *this);

}

//-------------------------------------
void PizzaEnemy::increaseJumps()
{
	m_jumps++;
}

void PizzaEnemy::movePizza(sf::Time delta)
{
	Enemy::move(delta);
}

