#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"
#include "GameObject/MovingObject/Entity.h"
#include "Macros.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/StaticObject/Obstacle.h"

class MovingSaltBomb;
class InGameState;

class Player :public Entity
{
public:
	Player(InGameState&);
	void move(sf::Time);
	Input getUserInput();
	void draw(sf::RenderWindow&)const override ;
	void increaseSaltBombs();
	void decreaseSaltBombs();
	int getSaltBombsAmount()const;
	void setCheesed(bool);
	bool isCheesed()const;
	void createBomb(std::unique_ptr< MovingSaltBomb>);
	void increaseHearts();
	void setCollideWithEnemy();
	int getHearts()const;
	void increaseCoins();
	int getCoins()const;
	
private:
	std::unique_ptr<PlayerState> m_state;
	float m_switchBlinkTime;
	int m_saltBombsStack;
	int m_hearts;
	int m_coins;
	int m_frame;
	int m_blinks;
	bool m_isCheesed;
	bool m_collideWithEnemy;
	sf::Time m_blinkTimer;
	InGameState& m_game;
};