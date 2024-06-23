#include "GameObject/MovingObject/Player.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include <iostream>

Player::Player(InGameState& game):m_game(game), m_frame(0), m_saltBombsStack(0), m_isCheesed(false), m_coins(0), m_hearts(5)
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

void Player::decreaseHearts()
{
	m_hearts--;
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
