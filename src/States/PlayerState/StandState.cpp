#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include "Player.h"
#include <iostream>

std::unique_ptr<PlayerState> StandState::handleEvent(Input input, Player& player)
{
   /* if (player.isOnGround() && input == SPACE)
        return std::make_unique<JumpState>();
    
    if (player.isOnGround() && (input == RIGHT || input == LEFT))
        return std::make_unique<WalkState>();*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return std::make_unique<JumpState>();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
        return std::make_unique<WalkState>();
   return nullptr;
}

void StandState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
    player.activateGravity(0.3f);
    float gravity = player.getGravity();
    //std::cout << "im in stand state the gravity is :" << gravity << std::endl;
    newPos.x = 0;
    newPos.y = gravity;
    player.setObjectPosition(newPos + player.getObjectSprite().getPosition());
    
    player.setAnimationRect(PlayerStateTypes::STAND, time);
}
