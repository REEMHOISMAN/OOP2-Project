#include "States/PlayerState/RunState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "Player.h"
#include "Macros.h"
#include <memory>


RunState::RunState() :m_acceleration(0){}

std::unique_ptr<PlayerState> RunState::handleEvent(Input input, Player& player)
{
	if (input == SPACE)
		return std::make_unique<JumpState>();
	if (input == RIGHT && player.isHeadDirectionRight() || input == LEFT && !player.isHeadDirectionRight())
		return nullptr;
	return std::make_unique<StandState>();
}

void RunState::update(sf::Time delta, Player& player)
{
	sf::Vector2f newPos;
	newPos.x = 150.5f * delta.asSeconds(); // same calculation as walk
	
	player.activateGravity(0.3f);
	auto gravity = player.getGravity();
	
	if (m_acceleration < 6.f) //until reach top;
		m_acceleration += 0.1f; //accelerate

	newPos.x += m_acceleration; // append the acceleration to the newX
	if (!player.isOnGround())
		newPos.x *= -1;
	
	player.setObjectPosition(player.getObjectSprite().getPosition() + newPos);
	player.setAnimationRect(PlayerStateTypes::RUN, delta);
}
