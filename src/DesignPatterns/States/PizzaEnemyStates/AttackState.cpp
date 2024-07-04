#pragma region Includes
#include "DesignPatterns/States/PizzaEnemyStates/AttackState.h"
#include "DesignPatterns/States/PizzaEnemyStates/MoveState.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "Macros.h"
#pragma endregion


/*================== AttackState Constructor =================*/
AttackState::AttackState(const ObjectAnimation animation, const sf::Time frameTimer) :
	PizzaEnemyState(animation, frameTimer), m_generateCheese(false)
{
}

/*================== AttackState handleTime =================*/
std::unique_ptr<PizzaEnemyState> AttackState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{
	if (m_generateCheese)
	{
		return std::make_unique<MoveState>(PIZZA_ENEMY_MOVE, sf::seconds(0.25f));
	}
	return nullptr;
}

/*================== AttackState update =================*/
/*----------------------------------------------------------
 * This state comes into action when the pizza monster wants to attack,
 * when a pizza monster attacks a new moving object is created 
 * which is the cheese moved by strategy
------------------------------------------------------------*/
void AttackState::update(const sf::Time deltaTime, PizzaEnemy& pizzaEnemy)
{
	m_generateCheese = setAnimationFrame(pizzaEnemy, deltaTime);
	if (!m_generateCheese) return;
	
	auto pos = pizzaEnemy.getPosition();
	m_cheese.setTexture(ResourceManager::instance().getTexture("cheese"));
	pos.y -= 30;
	m_cheese.setScale(1.5, 1.5);
	
	if (pizzaEnemy.isHeadDirectionRight()) {
		m_cheese.scale(-1, 1);
		pos.x += CHEESE_WEAPON_SPEED;
	}

	else {
		pos.x -= CHEESE_WEAPON_SPEED;
	}
	m_cheese.setPosition(pos);

	pizzaEnemy.createCheese(std::make_unique<CheeseBullet>(m_cheese, std::make_unique<SideToSideStrategy>(300.f), pizzaEnemy.isHeadDirectionRight()));
	
}
