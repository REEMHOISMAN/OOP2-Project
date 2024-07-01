#include "DesignPatterns/States/PizzaEnemyStates/DieState.h"
#include "GameObject/StaticObject/Pizza.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>

DieState::DieState(const ObjectAnimation type, const sf::Time frameTimer): PizzaEnemyState(type, frameTimer){}

//-------------------------------------------------
std::unique_ptr<PizzaEnemyState> DieState::handleTime(PizzaEnemy& pizzaEnemy, sf::Time deltaTime)
{
	return nullptr;
}

//-------------------------------------------------
void DieState::update(sf::Time time, PizzaEnemy& pizzaEnemy)
{
	
	bool end = false;
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
		sprite.setPosition(pizzaEnemy.getObjectSprite().getPosition().x, pizzaEnemy.getObjectSprite().getPosition().y + pizzaEnemy.getObjectSprite().getGlobalBounds().height/2-10.f);
		sprite.scale(1.7f,1.7f);
		pizzaEnemy.createPizza(std::make_unique<Pizza>(sprite));
		pizzaEnemy.setToErase();
	}
}
