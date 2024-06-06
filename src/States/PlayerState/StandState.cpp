#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include "Player.h"

StandState::StandState(Player& player, Input input) : PlayerState(player, input){}

std::unique_ptr<PlayerState> StandState::handleEvent(Input input, Player& player)
{
    if (input == LEFT || input == RIGHT) 
        return std::make_unique<WalkState>(player, input);
    if (input == SPACE)
        return std::make_unique<JumpState>(player, input);
   return nullptr;
}

void StandState::update(sf::Time time)
{
    setAnimation(PlayerStateTypes::STAND, time);
}
