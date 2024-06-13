 #include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/RunState.h"
#include "Macros.h"
#include "Player.h"

WalkState::WalkState() :m_walkTimer(0.f){}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{
    if (input == NONE) {
        return std::make_unique<StandState>();
    }

    if (input == SPACE && player.isOnGround()) {
        return std::make_unique<JumpState>();
    }

    if (m_walkTimer >= 2.f && player.isOnGround()) {
        return std::make_unique<RunState>();
    }

    return nullptr;
}

void WalkState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
   float sec = time.asSeconds();

   player.activateGravity(0.3f);
   float gravity = player.getGravity();
   newPos.x = time.asSeconds() * 150.f;
   newPos.y = gravity;
   
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
       newPos.x *= -1;
   
   auto prevPos = player.getObjectSprite().getPosition();
   if (prevPos.x < newPos.x + prevPos.x != player.isHeadDirectionRight())
   {
       player.setHeadDirection();
       player.setScale();
   }

   player.setObjectPosition(prevPos + newPos);
   
   player.setAnimationRect(PlayerStateTypes::WALK, time);
   m_walkTimer += sec;
}
