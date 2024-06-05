#pragma once
#include "States/PlayerState/PlayerState.h"
#include "Entity.h"

class Player :public Entity
{
public:
    Player(sf::Sprite&);
	void move(sf::Time);
	Input getInput();
	void draw(sf::RenderWindow&)const override ;
	void setPosition(const sf::Vector2f& pos);

private:
	std::unique_ptr<PlayerState> m_state;
	bool m_rightDirection;
};