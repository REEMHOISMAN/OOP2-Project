#pragma region Includes
#include"DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/DivingState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/States/PlayerState/BombState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "CollisionHandling.h"
#include "Macros.h"
#include "GameObject/MovingObject/Player.h"
#include <iostream>
#pragma endregion 


/*================== JumpState Constructor =================*/
JumpState::JumpState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1f)), 
								m_jumpSpeed(0.f), m_rightLeftSpeed(0.f), m_jumpTimer(0.f)
{
	ResourceManager::instance().playSound("jumpSound");
}

/*================== JumpState handleEvent =================*/
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{	
	int pizzaAmount = player.getPizzasAmount();
	if (player.isCheesed())
		return std::make_unique<CheesedState>(PLAYER_CHEESED);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && player.getSaltBombsAmount()>0)
		return std::make_unique<BombState>(PLAYER_STAND);

	if ((player.isOnGround() || player.isBlockedFromSide()))
		return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);

	if (m_jumpTimer >= 1.1f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player.isBlockedFromSide()&&player.getPizzasAmount()==0)
		return std::make_unique<DivingState>(PLAYER_DIVE);

	// fro here conditions to manage movment in the air 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !player.isBlockedFromSide())
		m_rightLeftSpeed = 150.f;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !player.isBlockedFromSide())
		m_rightLeftSpeed = -150.f;

	else if ((input == LEFT || input == RIGHT))
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;
	
	return nullptr;
}
/*================== JumpState update =================*/
/*---------------------------------------------------------
* this state as his name allow to the player to jump fro this state 
you can exit to dive state(make sure you dont holding pizza)
or to stand state
-----------------------------------------------------------*/

void JumpState::update(sf::Time elapsedTime, Player& player)
{
	float sec = elapsedTime.asSeconds();
	m_jumpSpeed = sec * PLAYER_JUMP_ACCELERATION;
	player.activateGravity(GRAVITY-0.1f);
    sf::Vector2f newPos;
	player.setClimb(false);

	float gravity = player.getGravity();
    player.isBlockedFromSide() ? newPos.x = 0.f :newPos.x = sec*m_rightLeftSpeed;
    newPos.y = -m_jumpSpeed+gravity;
    player.setObjectPosition(player.getPosition()+newPos);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) m_jumpTimer += sec;
	
	if ((newPos.x < 0 && player.isHeadDirectionRight()) ||
		(newPos.x > 0 && !player.isHeadDirectionRight()))
	{
		player.setHeadDirection(!player.isHeadDirectionRight());
		player.setScale();
	}

	
	player.setBlockedOnSide(false);

	m_rightLeftSpeed = 0;

	setAnimationFrame(player, elapsedTime);
}
