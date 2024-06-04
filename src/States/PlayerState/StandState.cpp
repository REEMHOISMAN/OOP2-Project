#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "Player.h"

StandState::StandState(Player& player) : PlayerState(player){}

std::unique_ptr<PlayerState> StandState::handleEvent(Input key, Player& player)
{
   // if (key == LEFT || key == RIGHT) return std::make_unique<WalkState>(player);
    //if (key == SPACE) return std::make_unique<JumpState>(player);
    return std::unique_ptr<PlayerState>();
}

void StandState::update(sf::Time){}
