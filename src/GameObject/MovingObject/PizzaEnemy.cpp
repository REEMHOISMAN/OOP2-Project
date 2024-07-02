#pragma region Includes
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"
#include "DesignPatterns/States/PizzaEnemyStates/DieState.h"
#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "GameObject/StaticObject/Pizza.h"
#include "Level.h"
#include <memory>
#pragma endregion

/*================== PizzaEnemy Register =================*/
bool PizzaEnemy::m_register = MovingObjectFactory::registerMovingObject(sf::Color(255, 201, 14),
	[](float x, float y, Level* level)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(PIZZA_ENEMY_MOVE);
		sf::Sprite sprite(ResourceManager::instance().getTexture("PizzaEnemySheet"));
		sprite.setTextureRect(animation[0]);
		sprite.setPosition(x, y);
		sprite.setScale(0.85f, 0.85f);
		level->inceasePizzaAmount();
		return std::make_unique<PizzaEnemy>(sprite, std::make_unique<SideToSideStrategy>(OBJECT_SPEED), *level);
	});

/*================== PizzaEnemy Constructor =================*/
PizzaEnemy::PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Level& game)
	: Enemy(sprite, std::move(strategy)), m_state(std::make_unique<MoveState>(PIZZA_ENEMY_MOVE, sf::seconds(0.25))), m_game(game) {}

/*================== move =================*/
void PizzaEnemy::move(const sf::Time& deltaTime)
{
	auto state = m_state->handleTime(*this, deltaTime);
	if (state) m_state = std::move(state);
	m_state->update(deltaTime, *this);
}

/*================== createCheese =================*/
void PizzaEnemy::createCheese(std::unique_ptr<CheeseBullet> cheese)
{
	m_game.insertMovingObject(std::move(cheese));
}

/*================== loadDieState =================*/
void PizzaEnemy::loadDieState()
{
	m_state = std::make_unique<DieState>(PIZZA_ENEMY_DIE, sf::seconds(0.15f));
}

/*================== createPizza =================*/
void PizzaEnemy::createPizza(std::unique_ptr<Pizza> pizza)
{
	m_game.insertStaticObject(std::move(pizza));
}

