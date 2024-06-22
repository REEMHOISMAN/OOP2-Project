#pragma once
#include "DesignPatterns/States/PlayerState/PlayerState.h"
#include "GameObject/MovingObject/Entity.h"
#include "Macros.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/StaticObject/Obstacle.h"

class Player :public Entity
{
public:
    Player(sf::Sprite&);
	void move(sf::Time);
	Input getUserInput();
	void draw(sf::RenderWindow&)const override ;
	void increaseSaltBombs();
	void decreaseSaltBombs();
	int getSaltBombsAmount()const;
	void setCheesed(bool);
	bool isCheesed()const;
	
private:
	std::unique_ptr<PlayerState> m_state;
	int m_saltBombsStack;
	int m_frame;
	bool m_isCheesed;
	sf::Time m_elapsed;
};