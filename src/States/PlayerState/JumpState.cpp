#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/DivingState.h"
#include "CollisionHandling.h"
#include "Macros.h"
#include "Player.h"

JumpState::JumpState(Player& player, Input input)
	: PlayerState(player, input),m_jumpSpeed(0), m_rightLeftSpeed(0), m_jumpTimer(0)
{
	resetGravity();
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{	
	if (m_jumpTimer >= 2.f)
		return std::make_unique<DivingState>(player, input);

	if ((input == LEFT || input == RIGHT) && !playerIsCollide())
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;

	if (playerIsCollide())//&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		return std::make_unique<StandState>(player, input);

	// if the user press left/right and he's in the AIR -> we need to update the "x" but still be in JumpStat
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_rightLeftSpeed = 150.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -150.f;
	return nullptr;
}
//---------------------------------------------------------
void JumpState::update(sf::Time elapsedTime)
{
	m_jumpSpeed = elapsedTime.asSeconds() * 600.f;
	
	if (!playerIsCollide())
		activateGravity(0.2f);
	else {
		resetGravity();
	}
	auto gravity = getGravity();
	float newX = elapsedTime.asSeconds() * m_rightLeftSpeed; //can be 0 if the user didnt press left/right
	float sec = elapsedTime.asSeconds();

	setPosition({newX,-m_jumpSpeed +gravity }); // new x (it was "0" before)


  	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_jumpTimer += sec;
	
	setAnimation(PlayerStateTypes::JUMP, elapsedTime);
	
	m_rightLeftSpeed = 0; // if the user wants to stop move left/right while he is in the air
}
