#include "DesignPatterns/States/PlayerState/DivingState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "CollisionHandling.h"
#include "GameObject/MovingObject/Player.h"
#include "Macros.h"

DivingState::DivingState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1)), m_rightLeftSpeed(0.f){}
//---------------------------------------------------------
std::unique_ptr<PlayerState> DivingState::handleEvent(Input input , Player& player)
{
	if (input != SPACE || player.isOnGround() || player.isBlockedFromSide())
	{
		player.resetGravity();
		return std::make_unique<StandState>(PLAYER_STAND);
	}
	
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
	setAnimationFrame(player, time);
}
//---------------------------------------------------------
