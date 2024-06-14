#include"States/PlayerState/JumpState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/DivingState.h"
#include "CollisionHandling.h"
#include "Macros.h"
#include "Player.h"
#include <iostream>

JumpState::JumpState()
	: m_jumpSpeed(0.f), m_rightLeftSpeed(0), m_jumpTimer(0){}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{	
	if (player.isOnGround() || player.isBlockedFromSide()) // ***put the second condition in "note" and run
		return std::make_unique<StandState>();
	
	if (m_jumpTimer >= 1.1f)
		return std::make_unique<DivingState>();

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_rightLeftSpeed = 150.f;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -150.f;

	else if ((input == LEFT || input == RIGHT))
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;
	
	return nullptr;
}

void JumpState::update(sf::Time elapsedTime, Player& player)
{
	float sec = elapsedTime.asSeconds();
	m_jumpSpeed = sec * 600.f;
	player.activateGravity(0.3f);
    sf::Vector2f newPos;
	
	float gravity = player.getGravity();
    player.isBlockedFromSide() ? newPos.x = 0.f :newPos.x = sec*m_rightLeftSpeed;
    newPos.y = -m_jumpSpeed+gravity;
    player.setObjectPosition(player.getObjectSprite().getPosition()+newPos);

	m_jumpTimer += sec;
	
	if ((newPos.x < 0 && player.isHeadDirectionRight()) ||
		(newPos.x > 0 && !player.isHeadDirectionRight()))
	{
		player.setHeadDirection();
		player.setScale();
	}

	player.setAnimationRect(PlayerStateTypes::JUMP, elapsedTime);
	
	player.setBlockedOnSide(false);

	m_rightLeftSpeed = 0;
}
