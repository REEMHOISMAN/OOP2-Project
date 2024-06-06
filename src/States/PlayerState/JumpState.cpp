#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/StandState.h"
#include "Macros.h"

JumpState::JumpState(Player& player, Input input)
	: PlayerState(player, input),m_pressingTime {0}
{
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{

	if (input ==SPACE) 
	{
		return std::make_unique<JumpState>(player, input);
	}
		
}
//---------------------------------------------------------
void JumpState::update(sf::Time elapsedTime)
{
	auto jumpSpeed = elapsedTime.asSeconds()*1.2f;
	sf::Vector2f velocity(getPlayerPosition().x, PLAYER_MIN_Y);
	setPosition({ velocity.x,velocity.y-jumpSpeed});

}
