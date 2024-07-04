#pragma region Includes
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/States/PlayerState/BombState.h"
#include "DesignPatterns/States/PlayerState/CrouchState.h"
#include "DesignPatterns/States/PlayerState/ClimbingState.h"
#include "GameObject/MovingObject/Player.h"
#include <iostream>
#pragma endregion 

/*================== StandState Constructor =================*/
StandState::StandState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1f)) {}

/*================== StandState handleEvent =================*/
std::unique_ptr<PlayerState> StandState::handleEvent(Input input, Player& player)
{
    int pizzaAmount = player.getPizzasAmount();
    if (player.isOnGround()) {  // Check if the player is on the ground
        if (input == SPACE) {
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
        if (input == CLIMB) {
            return std::make_unique<ClimbingState>(PLAYER_STAND);
        }
    }

    // If no valid input is processed, return nullptr indicating no state change
    return nullptr;
}

/*================== StandState update =================*/
/*---------------------------------------------------------
This is the player's default state from which you can reach
most of the player's states in the game, this state literally
is when the player does nothing
-----------------------------------------------------------*/
void StandState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
    player.setClimb(false);
    player.activateGravity(GRAVITY);
    float gravity = player.getGravity();
    newPos.x = 0;
    newPos.y = gravity;
    
    player.setObjectPosition(newPos + player.getObjectSprite().getPosition());
    
    setAnimationFrame(player, time);
}