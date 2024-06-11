
#include "States/PlayerState/DivingState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include "CollisionHandling.h"
#include "Macros.h"
#include "Player.h"

DivingState::DivingState(Player& player, Input input)
	:PlayerState(player, input),m_rightLeftSpeed(0.f)
{
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> DivingState::handleEvent(Input input , Player& player)
{
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || playerIsCollide())
		return std::make_unique<StandState>(player, input);
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_rightLeftSpeed = 3.f;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -3.f;
	return nullptr;
}
//---------------------------------------------------------
void DivingState::update(sf::Time time)
{
	if (!playerIsCollide()) {
  		activateGravity(0.01f);
	}
	auto gravity = getGravity();
	setPosition({ m_rightLeftSpeed,gravity });
	setAnimation(PlayerStateTypes::DIVE, time);
}
//---------------------------------------------------------

