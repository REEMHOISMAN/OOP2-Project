#include "DesignPatterns/States/PlayerState/ClimbingState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/MovingObject/Player.h"

ClimbingState::ClimbingState(const ObjectAnimation type)
	:PlayerState(type,sf::seconds(0.f)), m_climbSpeed(0.f), m_xSpeed(0.f)
{
}

std::unique_ptr<PlayerState> ClimbingState::handleEvent(Input input, Player& player)
{
	if (!player.isClimb())
	{
		return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);
	}
	if (input == SPACE)
	{
		return player.getPizzasAmount() == 0 ? std::make_unique<JumpState>(PLAYER_JUMP) : std::make_unique<JumpState>(PLAYER_JUMP_PIZZA);
	}
	if ((input == LEFT || input == RIGHT)) 
	{
		input == LEFT ? m_xSpeed = -200.f : m_xSpeed = 200.f;
	}	
	return nullptr;
}

void ClimbingState::update(sf::Time elapsed, Player& player)
{
	m_climbSpeed = elapsed.asSeconds() * 200.f;
	sf::Vector2f newPos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		newPos.y = -m_climbSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		newPos.y = m_climbSpeed;
	auto prevPos = player.getObjectSprite().getPosition();
	newPos.x = m_xSpeed * elapsed.asSeconds();
	setAnimationFrame(player, elapsed);
	player.setObjectPosition(prevPos+newPos);
	player.setClimb(false);
	m_xSpeed = 0.f;
}
