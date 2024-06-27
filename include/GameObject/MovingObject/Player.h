#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"
#include "GameObject/MovingObject/Entity.h"
#include "Macros.h"
#include "GameObject/StaticObject/Obstacle.h"
#include "GameObject/StaticObject/Pizza.h"

class MovingSaltBomb;
class InGameState;

class Player :public Entity
{
public:
	Player(InGameState&);
	void pickUpPizza(Pizza&);
	void move(sf::Time);
	Input getUserInput();
	void draw(sf::RenderWindow&)const override ;
	void increaseSaltBombs();
	void decreaseSaltBombs();
	int getSaltBombsAmount()const;
	void setCheesed(bool);
	bool isCheesed()const;
	void createBomb(std::unique_ptr< MovingSaltBomb>);
	void dropPizza(std::unique_ptr<Pizza>);
	void increaseHearts();
	void setCollideWithEnemy();
	int getHearts()const;
	void increaseCoins();
	int getCoins()const;
	void increasePizza();
	int getPizzasAmount()const;
	void HoldingPizzaTimer(sf::Time elapsed);
	float GetPizzaTimer()const;
	void resetPizzTimer();
	bool dropPizza()const;
	void setDropPizza(bool);
	void resetPizzaAmount();
	
private:
	std::unique_ptr<PlayerState> m_state;
	float m_switchBlinkTime;
	int m_saltBombsStack;
	int m_hearts;
	int m_coins;
	int m_pizzas;
	bool m_dropPizza;
	int m_frame;
	int m_blinks;
	bool m_isCheesed;
	bool m_collideWithEnemy;
	float m_pickedPizzaTimer;
	sf::Time m_blinkTimer;
	InGameState& m_game;
};