#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include "Player.h"

std::unique_ptr<PlayerState> StandState::handleEvent(Input input, Player& player)
{
    if (player.isOnGround() && input == SPACE)
        return std::make_unique<JumpState>();
    
    if (player.isOnGround() && (input == RIGHT || input == LEFT))
        return std::make_unique<WalkState>();

   return nullptr;
}

void StandState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
    player.activateGravity(0.3f);
    float gravity = player.getGravity();
    newPos.x = 0;
    newPos.y = gravity;
    player.setObjectPosition(newPos + player.getObjectSprite().getPosition());
    
    player.setAnimationRect(PlayerStateTypes::STAND, time);
}
