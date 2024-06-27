#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/States/PlayerState/BombState.h"
#include "DesignPatterns/States/PlayerState/CrouchState.h"
#include "GameObject/MovingObject/Player.h"
#include <iostream>

StandState::StandState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1)) {}

std::unique_ptr<PlayerState> StandState::handleEvent(Input input, Player& player)
{
    int pizzaAmount = player.getPizzasAmount();
    if (player.isOnGround()) {  // Check if the player is on the ground
        if (input == SPACE/* && pizzaAmount == 0*/) {
            player.setOnGround(false);
            return pizzaAmount == 0 ? std::make_unique<JumpState>(PLAYER_JUMP) : std::make_unique<JumpState>(PLAYER_JUMP_PIZZA);
        }
        if ((input == RIGHT || input == LEFT)) {
            return pizzaAmount == 0 ? std::make_unique<WalkState>(PLAYER_WALK) : std::make_unique<WalkState>(PLAYER_WALK_PIZZA);
        }
        if (player.isCheesed()) {
            return std::make_unique<CheesedState>(PLAYER_CHEESED);
        }
        if (input == ATTACK) {
            return std::make_unique<BombState>(PLAYER_STAND);
        }
        if (input == DOWN)
        {
            return std::make_unique<CrouchState>(PLAYER_CROUCH);
        }
    }

    // If no valid input is processed, return nullptr indicating no state change
    return nullptr;
}

void StandState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
    player.activateGravity(0.3);
    float gravity = player.getGravity();
    newPos.x = 0;
    newPos.y = gravity;
    
    player.setObjectPosition(newPos + player.getObjectSprite().getPosition());
    
    setAnimationFrame(player, time);
}