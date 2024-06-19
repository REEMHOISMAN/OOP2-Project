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
	
private:
	std::unique_ptr<PlayerState> m_state;

	int m_frame;
	sf::Time m_elapsed;
};