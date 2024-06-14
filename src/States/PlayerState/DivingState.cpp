
#include "States/PlayerState/DivingState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include "CollisionHandling.h"
#include "Macros.h"
#include "Player.h"

DivingState::DivingState():m_rightLeftSpeed(0.f){}
//---------------------------------------------------------
std::unique_ptr<PlayerState> DivingState::handleEvent(Input input , Player& player)
{
	if(input != SPACE)// || player.isOnGround())
		return std::make_unique<StandState>();
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_rightLeftSpeed = 3.f;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -3.f;
	return nullptr;
}
//---------------------------------------------------------
void DivingState::update(sf::Time time, Player& player)
{
	sf::Vector2f newPos;
	player.activateGravity(0.1f);
	auto gravity = player.getGravity();

	newPos.x = m_rightLeftSpeed;
	newPos.y = gravity*time.asSeconds();
	player.setObjectPosition(newPos + player.getObjectSprite().getPosition());
	player.setAnimationRect(PlayerStateTypes::DIVE, time);
}
//---------------------------------------------------------

