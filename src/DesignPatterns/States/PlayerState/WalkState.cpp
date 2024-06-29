#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/RunState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/States/PlayerState/BombState.h"
#include "Macros.h"
#include "GameObject/MovingObject/Player.h"

WalkState::WalkState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1f)), m_walkTimer(0.f){}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{
    int pizzaAmount = player.getPizzasAmount();
    if (player.isCheesed()) {
        return std::make_unique<CheesedState>(PLAYER_CHEESED);
    }
    
    if (input == NONE){
        return pizzaAmount == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)&& player.getSaltBombsAmount() > 0) {
        return pizzaAmount == 0 ? std::make_unique<BombState>(PLAYER_STAND) : std::make_unique<BombState>(PLAYER_STAND_PIZZA);
    }

    if (input == SPACE && player.isOnGround() && !player.isBlockedFromSide()) {
        player.setOnGround(false);
        return pizzaAmount == 0 ? std::make_unique<JumpState>(PLAYER_JUMP) : std::make_unique<JumpState>(PLAYER_JUMP_PIZZA);
    }
    if (m_walkTimer >= 1.1f && player.isOnGround()) {
        return pizzaAmount == 0 ? std::make_unique<RunState>(PLAYER_RUN) : std::make_unique<RunState>(PLAYER_RUN_PIZZA);
    }

    return nullptr;
}

void WalkState::update(sf::Time time, Player& player)
{
    sf::Vector2f newPos;
   float sec = time.asSeconds();
   player.activateGravity(0.3f); 
   player.setClimb(false);
   float gravity = player.getGravity();
   newPos.y = gravity;
   
   newPos.x  = gravity < 2.f? sec * 220.f: 0;


   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
       newPos.x *= -1;
      
   auto prevPos = player.getObjectSprite().getPosition();
   if ((newPos.x < 0 && player.isHeadDirectionRight()) || 
       (newPos.x > 0 && !player.isHeadDirectionRight()))
   {
       player.setHeadDirection(!player.isHeadDirectionRight());
       player.setScale();
   }

   player.setObjectPosition(prevPos + newPos);
   
   setAnimationFrame(player, time);
   player.setBlockedOnSide(false);
   m_walkTimer += sec;

}
