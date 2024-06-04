#include "WalkState.h"

WalkState::WalkState(Player& player) : PlayerState(player)
{
}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input, Player&)
{
    return std::unique_ptr<PlayerState>();
}

void WalkState::update(sf::Time)
{
    //fjdfodidjfoi
    //setPosition()
}
