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
	
	void setAnimationRect(PlayerStateTypes state, sf::Time delta);

private:
	std::unique_ptr<PlayerState> m_state;

	std::unordered_map<PlayerStateTypes, std::vector<sf::IntRect>> m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
};