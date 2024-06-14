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
	if (player.isOnGround() ||player.isBlockedFromSide())
	{
		return std::make_unique<StandState>();
	}
	if (m_jumpTimer >= 1.2f)
		return std::make_unique<DivingState>();

	else if ((input == LEFT || input == RIGHT) && !player.isBlockedFromSide()&&!player.isOnGround())
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_rightLeftSpeed = 150.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -150.f;
	// if the user press left/right and he's in the AIR -> we need to update the "x" but still be in JumpStat
	return nullptr;
}
void JumpState::update(sf::Time elapsedTime, Player& player)
{
	float sec = elapsedTime.asSeconds();
	m_jumpSpeed = sec * 600.f;
    player.activateGravity(0.2f);
    sf::Vector2f newPos;
	float gravity = player.getGravity();
    newPos.x = sec*m_rightLeftSpeed;
    newPos.y += -m_jumpSpeed+gravity;
    player.setObjectPosition(player.getObjectSprite().getPosition()+newPos);
	player.setOnGround(false);

	m_jumpTimer += sec;

	player.setAnimationRect(PlayerStateTypes::JUMP, elapsedTime);

	m_rightLeftSpeed = 0;
}
