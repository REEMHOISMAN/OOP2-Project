#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"


WalkState::WalkState(Player& player, Input input) : PlayerState(player, input)
{
}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{

    if (input == NONE) 
        return std::make_unique<StandState>(player, input);

    return std::make_unique<WalkState>(player, input);
}

void WalkState::update(sf::Time time)
{
    auto sec = time.asSeconds();
    auto input = getInput();
    if (input == LEFT) sec *= -1.f;

    setPosition({ sec, 0.f });
}
