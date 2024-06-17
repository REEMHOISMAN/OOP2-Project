 #include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/RunState.h"
#include "Macros.h"
#include "GameObject/MovingObject/Player.h"

WalkState::WalkState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1)), m_walkTimer(0.f){}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{
    if (input == NONE)
    {
        return std::make_unique<StandState>(PLAYER_STAND);
    }

    if (input == SPACE && player.isOnGround() && !player.isBlockedFromSide()) {
        player.setOnGround(false);
        return std::make_unique<JumpState>(PLAYER_JUMP);
    }

    if (m_walkTimer >= 1.1f && player.isOnGround()) {
        return std::make_unique<RunState>(PLAYER_RUN);
    }

    return nullptr;
}

void WalkState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
   float sec = time.asSeconds();
   player.activateGravity(0.3f); 

   float gravity = player.getGravity();
   newPos.y = gravity;
   
   newPos.x  = gravity < 2.f? sec * 220.f: 0;


   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
       newPos.x *= -1;
      
   auto prevPos = player.getObjectSprite().getPosition();
   if ((newPos.x < 0 && player.isHeadDirectionRight()) || 
       (newPos.x > 0 && !player.isHeadDirectionRight()))
   {
       player.setHeadDirection();
       player.setScale();
   }

   player.setObjectPosition(prevPos + newPos);
   
   setAnimationFrame(player, time);
   player.setBlockedOnSide(false);
   m_walkTimer += sec;

}
