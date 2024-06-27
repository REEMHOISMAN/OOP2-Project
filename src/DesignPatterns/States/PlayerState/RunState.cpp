#include "DesignPatterns/States/PlayerState/RunState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"

#include "GameObject/MovingObject/Player.h"
#include "Macros.h"
#include <memory>


RunState::RunState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.08)), m_acceleration(0){}

std::unique_ptr<PlayerState> RunState::handleEvent(Input input, Player& player)
{	
	int pizzaAmount = player.getPizzasAmount();
	if (player.isCheesed())
		return std::make_unique<CheesedState>(PLAYER_CHEESED);

	if (input != RIGHT && input != LEFT)
		return pizzaAmount == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);
	
	if (player.isOnGround()&&!player.isBlockedFromSide()&&input == SPACE)
		return pizzaAmount == 0 ? std::make_unique<JumpState>(PLAYER_JUMP) : std::make_unique<JumpState>(PLAYER_JUMP_PIZZA);

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
		player.setHeadDirection(!player.isHeadDirectionRight());
		player.setScale();
	}

	player.setObjectPosition(player.getObjectSprite().getPosition() + newPos);
	setAnimationFrame(player, delta);
}
