#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/RunState.h"
#include "Macros.h"

WalkState::WalkState(Player& player, Input input) : PlayerState(player, input), m_walkTimer(0.f)
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

    if (m_walkTimer >= 3.f)
        return std::make_unique<RunState>(player, input);
    
    return nullptr;
}

void WalkState::update(sf::Time time)
{
    auto input = getInput();
    float sec = time.asSeconds();
    float newX = sec * 150.5f;

    m_walkTimer += sec;
    if (input == LEFT)
        newX *= -1.f;
    setPosition({ newX, 0 });
    setAnimation(PlayerStateTypes::WALK, time);
}
