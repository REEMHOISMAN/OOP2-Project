#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/States/PizzaEnemyStates/DieState.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "GameObject/StaticObject/Pizza.h"
#include <memory>

bool PizzaEnemy::m_register = EnemyFactory::registerEnemy(sf::Color(255, 201, 14),
	[](float x, float y, InGameState* inGameState)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(PIZZA_ENEMY_MOVE);
		sf::Sprite sprite(ResourceManager::instance().getTexture("PizzaEnemySheet"));
		sprite.setTextureRect(animation[0]);
		sprite.setPosition(x, y);
		sprite.setScale(0.85f, 0.85f);
		return std::make_unique<PizzaEnemy>(sprite, std::make_unique<SideToSideStrategy>(220.f), *inGameState);
	});

//--------------------------------------------------------
PizzaEnemy::PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, InGameState& game)
	: Enemy(sprite, std::move(strategy)), m_state(std::make_unique<MoveState>(PIZZA_ENEMY_MOVE, sf::seconds(0.25))), m_game(game) {}

//--------------------------------------------------------
void PizzaEnemy::move(sf::Time deltaTime)
{
	auto state = m_state->handleTime(*this, deltaTime);
	if (state) m_state = std::move(state);
	m_state->update(deltaTime, *this);
}

//-------------------------------------
void PizzaEnemy::createCheese(std::unique_ptr<CheeseBullet> cheese)
{
	m_game.insertMovingObject(std::move(cheese));
}

//-----------------------------------------------------
void PizzaEnemy::loadDieState()
{
	m_state = std::make_unique<DieState>(PIZZA_ENEMY_DIE, sf::seconds(0.15f));
}


//-------------------------------------
void PizzaEnemy::createPizza(std::unique_ptr<Pizza> pizza)
{
	m_game.insertStaticObject(std::move(pizza));
}

