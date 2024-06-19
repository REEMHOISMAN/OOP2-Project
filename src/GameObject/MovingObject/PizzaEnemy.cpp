#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"

bool PizzaEnemy::m_register = EnemyFactory::registerEnemy(PIZZA_ENEMY_MOVE,
	[](auto& sprite, auto factor, auto enemyType)->std::unique_ptr<Enemy>
	{
		setEnemySprite(sprite, factor);
		return std::make_unique<PizzaEnemy>(sprite, std::make_unique<SideToSideStrategy>());
	});

//--------------------------------------------------------
PizzaEnemy::PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy)
	: Enemy(sprite, std::move(strategy)),m_WalkTimer(2.f),m_jumps(0), m_state(std::make_unique<MoveState>(PIZZA_ENEMY_MOVE)) {}

//--------------------------------------------------------
void PizzaEnemy::move(sf::Time deltaTime)
{
	//m_WalkTimer -= deltaTime.asSeconds();

	auto state = m_state->handleTime(*this, deltaTime);
	if (state) m_state = std::move(state);
	m_state->update(deltaTime, *this);

}

//-------------------------------------
void PizzaEnemy::increaseJumps()
{
	m_jumps++;
}

