#pragma once
#include "States/PlayerState/PlayerState.h"

class Player
{
public:
	Player();
	void move(sf::Time);
	Input getInput() const;
	void draw(sf::RenderWindow&)const;
	void setObjectPosition(const sf::Vector2f&); //for now - will be moved to entity/GameObject

private:
	std::unique_ptr<PlayerState> m_state;
	sf::Sprite m_sprite; //for now
};