#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "CollisionHandling.h"
#include "Macros.h"
#include "Player.h"

JumpState::JumpState(Player& player, Input input)
	: PlayerState(player, input),m_jumpSpeed(0), m_rightLeftSpeed(0), m_gravity(0)
{
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{			
	if ((input == LEFT || input == RIGHT) && player.inJumpState())
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;
	
	if (!player.inJumpState() || (playerIsCollide() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
		return std::make_unique<StandState>(player, input);
	// if the user press left/right and he's in the AIR -> we need to update the "x" but still be in JumpStat
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		 m_rightLeftSpeed = 150.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -150.f;
	
	return nullptr;
		
}
//---------------------------------------------------------
void JumpState::update(sf::Time elapsedTime)
{
	m_jumpSpeed = elapsedTime.asSeconds()*570.f;
	if (!playerIsCollide())
	{
		activateGravity(0.2f);
	}
	auto gravity = getGravity();
	float newX = elapsedTime.asSeconds() * m_rightLeftSpeed; //can be 0 if the user didnt press left/right
	setPosition({newX,-m_jumpSpeed +gravity }); // new x (it was "0" before)
	setAnimation(PlayerStateTypes::JUMP, elapsedTime);
	
	m_rightLeftSpeed = 0; // if the user wants to stop move left/right while he is in the air
}
