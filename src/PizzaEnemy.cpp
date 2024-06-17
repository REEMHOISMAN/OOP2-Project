#include "PizzaEnemy.h"
#include "Factories/EnemyFactory.h"

bool PizzaEnemy::m_register = EnemyFactory::registerEnemy(PIZZA_ENEMY,
	[](auto& sprite, auto&& strategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<PizzaEnemy>(sprite, std::move(strategy), animation); });