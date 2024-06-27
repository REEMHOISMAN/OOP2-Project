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

JumpState::JumpState(const ObjectAnimation animation) : PlayerState(animation, sf::seconds(0.1f)), 
								m_jumpSpeed(0.f), m_rightLeftSpeed(0.f), m_jumpTimer(0.f)
{
	ResourceManager::instance().playSound("jumpSound");
}

//---------------------------------------------------------
std::unique_ptr<PlayerState> JumpState::handleEvent(Input input , Player& player)
{	
	int pizzaAmount = player.getPizzasAmount();
	if (player.isCheesed())
		return std::make_unique<CheesedState>(PLAYER_CHEESED);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && player.getSaltBombsAmount()>0)
		return std::make_unique<BombState>(PLAYER_STAND);

	if ((player.isOnGround() || player.isBlockedFromSide()))
		return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);

	if (m_jumpTimer >= 1.1f && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		return std::make_unique<DivingState>(PLAYER_DIVE);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_rightLeftSpeed = 150.f;
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_rightLeftSpeed = -150.f;

	else if ((input == LEFT || input == RIGHT))
		input == LEFT ? m_rightLeftSpeed = -150.f : m_rightLeftSpeed = 150.f;
	
	return nullptr;
}

void JumpState::update(sf::Time elapsedTime, Player& player)
{
	float sec = elapsedTime.asSeconds();
	m_jumpSpeed = sec * 700.f;
	player.activateGravity(0.2f);
    sf::Vector2f newPos;
	
	float gravity = player.getGravity();
    player.isBlockedFromSide() ? newPos.x = 0.f :newPos.x = sec*m_rightLeftSpeed;
    newPos.y = -m_jumpSpeed+gravity;
    player.setObjectPosition(player.getObjectSprite().getPosition()+newPos);
	

	m_jumpTimer += sec;
	
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
