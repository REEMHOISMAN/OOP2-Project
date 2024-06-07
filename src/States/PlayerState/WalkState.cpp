#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "Macros.h"

WalkState::WalkState(Player& player, Input input) : PlayerState(player, input)
{
}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{

    if (input == NONE) 
        return std::make_unique<StandState>(player, input);

    if (input == SPACE)
        return std::make_unique<JumpState>(player, input);

    if (input !=getInput())
        return std::make_unique<WalkState>(player, input);
    
    return nullptr;
}

void WalkState::update(sf::Time time)
{
    auto sec = time.asSeconds();
    auto input = getInput();
    float newX = sec * 150.5f;
    if (input == LEFT)
        newX *= -1.f;
    setPosition({ newX, 0 });
    setAnimation(PlayerStateTypes::WALK, time);
}
