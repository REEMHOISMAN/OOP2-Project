 #include "States/PlayerState/WalkState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "States/PlayerState/RunState.h"
#include "Macros.h"
#include "Player.h"

WalkState::WalkState(Player& player, Input input) : PlayerState(player, input), m_walkTimer(0.f)
{
}

std::unique_ptr<PlayerState> WalkState::handleEvent(Input input, Player&player)
{
    if (input == NONE )
        return std::make_unique<StandState>(player, input);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerIsCollide())
        return std::make_unique<JumpState>(player, input);

    if (input !=getInput() && playerIsCollide())
        return std::make_unique<WalkState>(player, input);

    if (m_walkTimer >= 2.f && playerIsCollide())
        return std::make_unique<RunState>(player, input);
    
    return nullptr;
}

void WalkState::update(sf::Time time)
{
   float sec = time.asSeconds();
   float gravity = getGravity();
   float newX = time.asSeconds() * 150.f;
   if (!playerIsCollide()) {
       activateGravity(0.3f);
   }
   else {
       resetGravity();
   }
   
   if (getInput() == RIGHT)
       setPosition({ newX, gravity });
   else
       setPosition({ -newX, gravity });
   
   setAnimation(PlayerStateTypes::WALK, time);
   m_walkTimer += sec;
}
