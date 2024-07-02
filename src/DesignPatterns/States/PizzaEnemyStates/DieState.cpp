#pragma region Includes
#include "DesignPatterns/States/PizzaEnemyStates/DieState.h"
#include "GameObject/StaticObject/Pizza.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>
#pragma endregion 

/*================== DieState Constructor =================*/
DieState::DieState(const ObjectAnimation type, const sf::Time frameTimer): PizzaEnemyState(type, frameTimer){}

/*================== DieState handleTime =================*/
std::unique_ptr<PizzaEnemyState> DieState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{
	return nullptr;
}

/*================== DieState update =================*/
/*----------------------------------------------------------
This state comes into action when the pizza monster coliided with salt bomb,
after the pizza monster died new static object insert to the list of static objects
which is the pizza the player need to pick up moved by strategy, 
from this state the pizza not exist any more(deleted from the list)
------------------------------------------------------------*/

void DieState::update(sf::Time time, PizzaEnemy& pizzaEnemy)
{
	
	bool end = false;

	// here we make sure the pizza enemy die on the ground 
	if (!pizzaEnemy.isOnGround()) {
		auto sprite = pizzaEnemy.getObjectSprite();
		sprite.move(0.f, 3.f);
		pizzaEnemy.setObjectSprite(sprite);
	}
	else {
		end = setAnimationFrame(pizzaEnemy, time);
	}
	if (end)
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("pizza"));
		sprite.setTextureRect(sf::IntRect(42, 0, 42, 10));
		sprite.setPosition(pizzaEnemy.getPosition().x, pizzaEnemy.getPosition().y + pizzaEnemy.getGlobalBounds().height/2-10.f);
		sprite.scale(1.7f,1.7f);
		pizzaEnemy.createPizza(std::make_unique<Pizza>(sprite));
		pizzaEnemy.setToErase();
	}
}
