#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"
#include "GameObject/MovingObject/Entity.h"
#include "Macros.h"
#include "GameObject/StaticObject/Obstacle.h"
#include "GameObject/StaticObject/Pizza.h"

class MovingSaltBomb;
class Level;
class Cage;

class Player :public Entity
{
public:
	Player(Level&, Cage* = nullptr);
	void pickUpPizza(Pizza&);
	void move(const sf::Time&);
	Input getUserInput()const;
	void draw(sf::RenderWindow&)const override ;
	void increaseSaltBombs();
	void decreaseSaltBombs();
	int getSaltBombsAmount()const;
	void setCheesed(bool);
	bool isCheesed()const;
	void createBomb(std::unique_ptr< MovingSaltBomb>);
	void insertNewPizza(std::unique_ptr<Pizza>);
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
	void setPlayer(float, float);
	void resetPlayer();
	void setCage(Cage*);
	void rescueFriend();
	void setClimb(bool);
	bool isClimb()const;
	
private:
	std::unique_ptr<PlayerState> m_state;

	Cage* m_cage;
	float m_switchBlinkTime;
	int m_saltBombsStack;
	int m_hearts;
	int m_coins;
	int m_pizzas;
	int m_frame;
	int m_blinks;
	bool m_dropPizza;
	bool m_isCheesed;
	bool m_collideWithEnemy;
	bool m_climb;
	float m_pickedPizzaTimer;
	sf::Time m_blinkTimer;
	Level& m_level;
};