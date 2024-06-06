#include "States/PlayerState/JumpState.h"
#include "Macros.h"
JumpState::JumpState(Player& player, Input input)
	:m_pressingTime{ 0 }, PlayerState(player, input)
{
}
//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{
	if(input!=getInput())
		return std::make_unique<JumpState>(player,input);
}
//---------------------------------------------------------
void JumpState::update(sf::Time elapsedTime)
{
	auto jumpSpeed = elapsedTime.asSeconds()*1.2f;
	//sf::Vector2f velocity(,PLAYER_MIN_Y);


}
