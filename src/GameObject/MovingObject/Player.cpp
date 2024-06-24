#include "GameObject/MovingObject/Player.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include <iostream>

Player::Player(InGameState& game) :
	m_game(game), m_frame(0), m_saltBombsStack(0), m_isCheesed(false), m_coins(0),
	m_hearts(5), m_collideWithEnemy(false), m_blinks(0), m_blinkTimer(sf::seconds(0.f)), m_switchBlinkTime(0.2f)
{
	m_state = std::make_unique<StandState>(PLAYER_STAND);
}

//-----------------------------------------
void Player::move(sf::Time time)
{
 	auto input = getUserInput();
	auto state = m_state->handleEvent(input, *this);
	if (state) m_state = std::move(state);
	m_state->update(time, *this);
	if (m_blinkTimer > sf::seconds(0.f))
	{
		if (m_switchBlinkTime <= 0.f)
		{
			m_blinks++;
			m_switchBlinkTime = 0.2f;
		}
		m_switchBlinkTime -= time.asSeconds();
		m_blinkTimer -= time;
	}
}

//-----------------------------------------
Input Player::getUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return SPACE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) return ATTACK;
	return NONE;
}

void Player::draw(sf::RenderWindow& window)const
{
	auto sprite = getObjectSprite();
	auto center = sf::Vector2f(sprite.getPosition().x, HEIGHT/2);
	window.setView(sf::View(center, sf::Vector2f(WIDTH, HEIGHT)));
	
	if (m_blinkTimer > sf::seconds(0.f) && m_blinks % 2 != 0)
		return;

	GameObject::draw(window);
}

void Player::increaseSaltBombs() 
{
	m_saltBombsStack++;
}
void Player::decreaseSaltBombs()
{
	m_saltBombsStack--;
}
int Player::getSaltBombsAmount()const
{
	return m_saltBombsStack;
}

//--------------------------------
void Player::setCheesed(bool cheesed)
{
	m_isCheesed = cheesed;
}

//--------------------------------
bool Player::isCheesed() const
{
	return m_isCheesed;
}

void Player::createBomb(std::unique_ptr<MovingSaltBomb> salt)
{
	m_game.insertMovingObject(std::move(salt));
}

void Player::increaseHearts()
{
	if (m_hearts < 5)
		m_hearts++;
}

void Player::setCollideWithEnemy()
{
	if (m_blinkTimer <= sf::seconds(0.f))
	{
		m_blinkTimer = sf::seconds(1.5f);
		m_hearts--;
	}
}

int Player::getHearts() const
{
	return m_hearts;
}

void Player::increaseCoins()
{
	m_coins++;
}

int Player::getCoins() const
{
	return m_coins;
}
