#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "Macros.h"

JumpState::JumpState(Player& player, Input input)
	: PlayerState(player, input),m_jumpSpeed {0}
{
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{
	if (input == NONE && getPlayerPosition().y>=PLAYER_MIN_Y)
		return std::make_unique<StandState>(player, input);
	if (input == LEFT || input == RIGHT)
		return std::make_unique<WalkState>(player, input);
	return nullptr;
		
}
//---------------------------------------------------------
void JumpState::update(sf::Time elapsedTime)
{
	m_jumpSpeed = elapsedTime.asSeconds()*500.f;
	static float gravity = 0;
	auto playerPostion = getPlayerPosition();
	if (playerPostion.y >= PLAYER_MIN_Y)
	{
		gravity = 0;
		setPosition({0,0});
	}
	setPosition({0,-m_jumpSpeed + gravity });
	if (playerPostion.y < PLAYER_MIN_Y) {
		gravity+=0.1f;
	}
}
