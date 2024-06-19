#pragma once 
#include <memory>
#include <SFML/Graphics.hpp>
class PizzaEnemy;
class Enemy;
class PizzaEnemyState 
{
public:
	PizzaEnemyState()=default;
	virtual ~PizzaEnemyState() = default;
	virtual std::unique_ptr<PizzaEnemyState> handleTime(PizzaEnemy&,float&, sf::Time ) = 0;
	virtual void update(sf::Time, PizzaEnemy&) = 0;
};