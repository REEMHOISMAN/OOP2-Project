#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"
#include "Macros.h"

WalkState::WalkState(Player& player, Input input) : PlayerState(player, input)
{
}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{

    if (input == NONE) 
        return std::make_unique<StandState>(player, input);

    if (input !=getInput())
        return std::make_unique<WalkState>(player, input);
    
    return nullptr;
}

void WalkState::update(sf::Time time)
{
    auto sec = time.asSeconds();
    auto input = getInput();
    float newX = sec * 1.2f;
    if (input == LEFT)
        newX *= -1.f;

    setPosition({ newX, 0.f });
    setAnimation(PlayerStateTypes::WALK, time);
}
