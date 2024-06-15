#include "States/PlayerState/RunState.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/JumpState.h"
#include "Player.h"
#include "Macros.h"
#include <memory>


RunState::RunState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.08)), m_acceleration(0){}

std::unique_ptr<PlayerState> RunState::handleEvent(Input input, Player& player)
{	
	if ((input != RIGHT && input != LEFT))
		return std::make_unique<StandState>(PLAYER_STAND);
	
	if (player.isOnGround()&&!player.isBlockedFromSide()&&input == SPACE)
		return std::make_unique<JumpState>(PLAYER_JUMP);

	return nullptr;
}

void RunState::update(sf::Time delta, Player& player)
{
	sf::Vector2f newPos;
	newPos.x = 220.f * delta.asSeconds(); // same calculation as walk
	
	player.activateGravity(0.3f);
	auto gravity = player.getGravity();
	
	if (m_acceleration < 2.f) //until reach top;
		m_acceleration += 0.1f; //accelerate

	newPos.x += m_acceleration; // append the acceleration to the newX
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		newPos.x *= -1;
	newPos.y = gravity;

	if ((newPos.x < 0 && player.isHeadDirectionRight()) ||
		(newPos.x > 0 && !player.isHeadDirectionRight()))
	{
		player.setHeadDirection();
		player.setScale();
	}

	player.setObjectPosition(player.getObjectSprite().getPosition() + newPos);
	setAnimationFrame(player, delta);
}
