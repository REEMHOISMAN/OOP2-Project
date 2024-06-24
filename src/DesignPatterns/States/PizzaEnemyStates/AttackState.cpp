#include "DesignPatterns/States/PizzaEnemyStates/AttackState.h"
#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

AttackState::AttackState(const ObjectAnimation animation, const sf::Time& frameTimer) :
	PizzaEnemyState(animation, frameTimer), m_generateCheese(false)
{

}

std::unique_ptr<PizzaEnemyState> AttackState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{
	if (m_generateCheese)
	{
		return std::make_unique<MoveState>(PIZZA_ENEMY_MOVE, sf::seconds(0.25f));
	}
	return nullptr;
}

//--------------------------------------------------
void AttackState::update(sf::Time deltaTime, PizzaEnemy& pizzaEnemy)
{
	m_generateCheese = setAnimationFrame(pizzaEnemy, deltaTime);
	if (!m_generateCheese) return;
	
	auto pos = pizzaEnemy.getObjectSprite().getPosition();
	m_cheese.setTexture(ResourceManager::instance().getTexture("cheese"));
	pos.y -= 30;
	m_cheese.setScale(1.5, 1.5);
	
	if (pizzaEnemy.isHeadDirectionRight()) {
		m_cheese.scale(-1, 1);
		pos.x += 110;
	}

	else {
		pos.x -= 110;
	}
	m_cheese.setPosition(pos);

	pizzaEnemy.createCheese(std::make_unique<CheeseBullet>(m_cheese, std::make_unique<SideToSideStrategy>(300.f), pizzaEnemy.isHeadDirectionRight()));
	
}
