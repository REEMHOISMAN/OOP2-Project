#include "DesignPatterns/States/PizzaEnemyStates/DieState.h"
#include "GameObject/StaticObject/Pizza.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>

DieState::DieState(const ObjectAnimation type): PizzaEnemyState(type){}

//-------------------------------------------------
std::unique_ptr<PizzaEnemyState> DieState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{
	return nullptr;
}

//-------------------------------------------------
void DieState::update(sf::Time time, PizzaEnemy& pizzaEnemy)
{
	bool end = setAnimationFrame(pizzaEnemy, time);
	
	if (end)
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("pizza"));
		pizzaEnemy.createPizza(std::make_unique<Pizza>(sprite));
	}
}
