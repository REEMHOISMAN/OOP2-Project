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
	void setPosition(const sf::Vector2f& pos);
	void exitJumpState();
	void setPlayerOnGround(bool);
	
	void setAnimationRect(PlayerStateTypes state, sf::Time delta);
	bool inJumpState()const;
	bool isGrounded()const;
	


private:
	std::unique_ptr<PlayerState> m_state;
	bool m_rightDirection;
	bool m_inJumpState;
	bool m_grounded;

	std::unordered_map<PlayerStateTypes, std::vector<sf::IntRect>> m_animation;
	int m_animationIndex;
	sf::Time m_elapsed;
};