#include "DesignPatterns/States/PlayerState/ClimbingState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/MovingObject/Player.h"

ClimbingState::ClimbingState(const ObjectAnimation type)
	:PlayerState(type,sf::seconds(0.1)), m_climbSpeed(0.f)
{
}

std::unique_ptr<PlayerState> ClimbingState::handleEvent(Input input, Player& player)
{
	if (!player.isOnGround())
	{
		return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);
	}
	if (input == SPACE)
	{
		return player.getPizzasAmount() == 0 ? std::make_unique<JumpState>(PLAYER_JUMP) : std::make_unique<JumpState>(PLAYER_JUMP_PIZZA);
	}
	if (input == LEFT || input == RIGHT) 
	{
		return player.getPizzasAmount() == 0 ? std::make_unique<WalkState>(PLAYER_WALK) : std::make_unique<WalkState>(PLAYER_WALK_PIZZA);
	}	
	return nullptr;
}

void ClimbingState::update(sf::Time elapsed, Player& player)
{
	player.activateGravity(0);
	m_climbSpeed = elapsed.asSeconds() * 200.f;
	sf::Vector2f newPos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		newPos.y = -m_climbSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		newPos.y = m_climbSpeed;
	auto prevPos = player.getObjectSprite().getPosition();
	player.setObjectPosition(prevPos+newPos);
}
