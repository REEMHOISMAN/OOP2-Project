#include "States/PlayerState/RunState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "Macros.h"
#include <memory>


RunState::RunState(Player& player, Input input) : PlayerState(player, input),m_acceleration(0){}

std::unique_ptr<PlayerState> RunState::handleEvent(Input input, Player& player)
{
	if (input == SPACE)
		return std::make_unique<JumpState>(player, input);
	if (input != getInput())
		return std::make_unique<StandState>(player, input);
	return nullptr;
}

void RunState::update(sf::Time delta)
{
	float newX = 150.5f * delta.asSeconds(); // same calculation as walk
	
	if (m_acceleration < 6.f) //until reach top;
		m_acceleration += 0.1f; //accelerate

	newX += m_acceleration; // append the acceleration to the newX
	if (getInput() == LEFT)
		newX *= -1;
	
	setPosition({ newX , 0 });
	setAnimation(PlayerStateTypes::RUN, delta);
}
