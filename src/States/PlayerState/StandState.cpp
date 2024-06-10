#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include "Player.h"

StandState::StandState(Player& player, Input input) : PlayerState(player, input){}

std::unique_ptr<PlayerState> StandState::handleEvent(Input input, Player& player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&playerIsCollide())
        return std::make_unique<JumpState>(player, input);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
        return std::make_unique<WalkState>(player, input);
   return nullptr;
}

void StandState::update(sf::Time time)
{
    if (!playerIsCollide()) {
        activateGravity(0.3f);
    }
    else {
        resetGravity();
    }
    auto gravity = getGravity();   
    setPosition({ 0, gravity });
    setAnimation(PlayerStateTypes::STAND, time);
}
