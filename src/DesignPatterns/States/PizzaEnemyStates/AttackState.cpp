#include "DesignPatterns/States/PizzaEnemyStates/AttackState.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "GameObject/MovingObject/CheeseWeapon.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

AttackState::AttackState(const ObjectAnimation animation) :
	PizzaEnemyState(animation), m_generateCheese(false)
{

}

std::unique_ptr<PizzaEnemyState> AttackState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{
	return nullptr;
}

//--------------------------------------------------
void AttackState::update(sf::Time deltaTime, PizzaEnemy& pizzaEnemy)
{
	m_generateCheese = setAnimationFrame(pizzaEnemy, deltaTime);
	if (m_generateCheese)
	{
		//m_cheese.setTexture()
		//std::make_unique<CheeseWeapon>()
	}
}
