#pragma once
#include "States/PlayerState/PlayerState.h"
#include "GameObject.h"

class Player//:public GameObject
{
public:
	Player();
	void move(sf::Time);
	Input getInput();
	void draw(sf::RenderWindow&)const;
	void setObjectPosition(const sf::Vector2f&); //for now - will be moved to entity/GameObject

private:
	std::unique_ptr<PlayerState> m_state;
	sf::Sprite m_sprite; //for now
	bool m_rightDirection;
};