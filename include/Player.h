#pragma once
#include "States/PlayerState/PlayerState.h"
#include "Entity.h"
#include "Macros.h"
#include "Player.h"
#include "Obstacle.h"

class Player :public Entity
{
public:
    Player(sf::Sprite&);
	void move(sf::Time);
	Input getUserInput();
	void draw(sf::RenderWindow&)const override ;
	
private:
	std::unique_ptr<PlayerState> m_state;

	int m_frame;
	sf::Time m_elapsed;
};