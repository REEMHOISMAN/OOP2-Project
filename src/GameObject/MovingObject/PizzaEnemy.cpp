#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "GameObject/StaticObject/Pizza.h"

bool PizzaEnemy::m_register = EnemyFactory::registerPizzaEnemy(PIZZA_ENEMY_MOVE,
	[](auto& sprite, auto factor, auto enemyType, auto& game)->std::unique_ptr<Enemy>
	{
		setEnemySprite(sprite, factor);
		return std::make_unique<PizzaEnemy>(sprite, std::make_unique<SideToSideStrategy>(220.f), game);
	});

//--------------------------------------------------------
PizzaEnemy::PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, InGameState& game)
	: Enemy(sprite, std::move(strategy)), m_state(std::make_unique<MoveState>(PIZZA_ENEMY_MOVE)), m_game(game) {}

//--------------------------------------------------------
void PizzaEnemy::move(sf::Time deltaTime)
{
	auto state = m_state->handleTime(*this, deltaTime);
	if (state) m_state = std::move(state);
	m_state->update(deltaTime, *this);
}

//-------------------------------------
void PizzaEnemy::createCheese(std::unique_ptr<Weapon> cheese)
{
	m_game.insertMovingObject(std::move(cheese));
}

void PizzaEnemy::createPizza(std::unique_ptr<Pizza> pizza)
{
	m_game.insertStaticObject(std::move(pizza));
}

