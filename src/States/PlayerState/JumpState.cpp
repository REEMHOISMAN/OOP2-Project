#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "Macros.h"

JumpState::JumpState(Player& player, Input input)
	: PlayerState(player, input),m_jumpSpeed(0), m_rightLeftSpeed(0), m_gravity(0)
{
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{
	if (input == NONE && getPlayerPosition().y>=PLAYER_MIN_Y)
		return std::make_unique<StandState>(player, input);
	
	// if the user press left/right and he's on the GROUND
	if ((input == LEFT || input == RIGHT) && getPlayerPosition().y >= PLAYER_MIN_Y)
		return std::make_unique<WalkState>(player, input);
	
	// if the user press left/right and he's in the AIR -> we need to update the "x" but still be in JumpState
	else if (input == LEFT || input == RIGHT)
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;
	
	return nullptr;
		
}
//---------------------------------------------------------
void JumpState::update(sf::Time elapsedTime)
{
	m_jumpSpeed = elapsedTime.asSeconds()*570.f;
	float newX = elapsedTime.asSeconds() * m_rightLeftSpeed; //can be 0 if the user didnt press left/right
	auto playerPostion = getPlayerPosition();
	if (playerPostion.y >= PLAYER_MIN_Y)
	{
		m_gravity = 0;
	}
	setPosition({newX,-m_jumpSpeed + m_gravity }); // new x (it was "0" before)
	setAnimation(PlayerStateTypes::JUMP, elapsedTime);
	if (playerPostion.y < PLAYER_MIN_Y) {
		m_gravity +=0.1f;
	}
	m_rightLeftSpeed = 0; // if the user wants to stop move left/right while he is in the air
}
