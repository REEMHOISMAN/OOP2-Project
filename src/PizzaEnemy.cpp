#include "PizzaEnemy.h"
#include "Factories/EnemyFactory.h"
#include "Strategies/UpDownStrategy.h"

bool PizzaEnemy::m_register = EnemyFactory::registerEnemy(PIZZA_ENEMY_MOVE,
	[](auto& sprite, auto&& strategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<PizzaEnemy>(sprite, std::move(strategy), animation); });

PizzaEnemy::PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
	: Enemy(sprite, std::move(strategy), animation),m_WalkTimer(2.f),m_jumps(0) {}

void PizzaEnemy::move(sf::Time deltaTime)
{
	m_WalkTimer -= deltaTime.asSeconds();
	if (m_WalkTimer<= 0.f) 
	{
		float posX = deltaTime.asSeconds() * 100.f;
		loadStrategy(std::move(std::make_unique< UpDownStrategy>(posX)));
		m_WalkTimer = 2.f;
	}
	Enemy::move(deltaTime);
}

void PizzaEnemy::increaseJumps()
{
	m_jumps++;
}

