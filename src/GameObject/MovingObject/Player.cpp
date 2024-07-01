#pragma region Includes
#include "GameObject/MovingObject/Player.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/CrouchState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "DesignPatterns/States/PlayerState/PlayerState.h"
#include "DesignPatterns/States/PlayerState/ClimbingState.h"
#include "GameObject/MovingObject/Cage.h"
#include "Level.h"
#include <iostream>
#pragma endregion
/*================== Player Constructor =================*/
Player::Player(Level& level, Cage* cage) : m_cage(cage),
	m_level(level), m_frame(0), m_saltBombsStack(0), m_isCheesed(false), m_coins(0),
	m_hearts(5), m_collideWithEnemy(false), m_blinks(0), m_blinkTimer(sf::seconds(0.f)),
	m_switchBlinkTime(0.2f),m_pizzas(0),m_pickedPizzaTimer(0.f),m_dropPizza(true), m_climb(false)
{
	m_state = std::make_unique<StandState>(PLAYER_STAND);
}

/*================== move =================*/
void Player::move(const sf::Time& time)
{
 	auto input = getUserInput();
	auto state = m_state->handleEvent(input, *this);
	if (state) m_state = std::move(state);
	m_state->update(time, *this);
	
	// when the player collide with enemy-->blink player
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

/*================== getUserInput =================*/
Input Player::getUserInput()const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return SPACE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return DOWN;
	if (m_climb)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return CLIMB;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return CLIMB;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) return ATTACK;
	
	return NONE;
}

/*================== draw =================*/
void Player::draw(sf::RenderWindow& window)const
{
	auto center = sf::Vector2f(getPosition().x, HEIGHT/2);
	if (getPosition().y < HEIGHT/2) {

		(!isOnGround() || m_climb|| window.getView().getCenter().y < getPosition().y ) ? 
			center.y = getPosition().y : center.y = window.getView().getCenter().y;

		window.setView(sf::View(center, sf::Vector2f(WIDTH, HEIGHT)));
	}
	else {
		window.setView(sf::View(center, sf::Vector2f(WIDTH, HEIGHT)));
	}
	
	if (m_blinkTimer > sf::seconds(0.f) && m_blinks % 2 != 0)
		return;

	GameObject::draw(window);
}

/*================== increaseSaltBombs =================*/
void Player::increaseSaltBombs() 
{
	m_saltBombsStack++;
}

/*================== decreaseSaltBombs =================*/
void Player::decreaseSaltBombs()
{
	m_saltBombsStack--;
}

/*================== getSaltBombsAmount =================*/
int Player::getSaltBombsAmount()const
{
	return m_saltBombsStack;
}

/*================== setCheesed =================*/
void Player::setCheesed(bool cheesed)
{
	m_isCheesed = cheesed;
}

/*================== isCheesed =================*/
bool Player::isCheesed() const
{
	return m_isCheesed;
}

/*================== createBomb =================*/
void Player::createBomb(std::unique_ptr<MovingSaltBomb> salt)
{
	m_level.insertMovingObject(std::move(salt));
}

/*================== insertNewPizza =================*/
void Player::insertNewPizza(std::unique_ptr<Pizza>pizza)
{
	m_level.insertStaticObject(std::move(pizza));
}

/*================== increaseHearts =================*/
void Player::increaseHearts()
{
	if (m_hearts < 5)
		m_hearts++;
}

/*================== setCollideWithEnemy =================*/
void Player::setCollideWithEnemy()
{
	if (m_blinkTimer <= sf::seconds(0.f))
	{
		m_blinkTimer = sf::seconds(1.5f);
		m_hearts--;
		ResourceManager::instance().playSound("playerEnemySound");
	}

}

/*================== getHearts =================*/
int Player::getHearts() const
{
	return m_hearts;
}

/*================== increaseCoins =================*/
void Player::increaseCoins()
{
	m_coins++;
}

/*================== getCoins =================*/
int Player::getCoins() const
{
	return m_coins;
}

/*================== increasePizza =================*/
void Player::increasePizza()
{
	m_pizzas++;
}

/*================== getPizzasAmount =================*/
int Player::getPizzasAmount() const
{
	return m_pizzas;
}

/*================== HoldingPizzaTimer =================*/
void Player::HoldingPizzaTimer(sf::Time elapsed)
{
	m_pickedPizzaTimer += elapsed.asSeconds();
}

/*================== GetPizzaTimer =================*/
float Player::GetPizzaTimer() const
{
	return m_pickedPizzaTimer;
}

/*================== resetPizzTimer =================*/
void Player::resetPizzTimer()
{
	m_pickedPizzaTimer = 0.f;
}
/*================== dropPizza =================*/
bool Player::dropPizza() const
{
	return m_dropPizza;
}

/*================== dropPizza =================*/
void Player::setDropPizza(bool value)
{
	m_dropPizza = value;
}

/*================== resetPizzaAmount =================*/
void Player::resetPizzaAmount()
{
	m_pizzas = 0;
}

/*================== setPlayer =================*/
void Player::setPlayer(float x, float y)
{
	auto sprite = getObjectSprite();
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(174, 50), sf::Vector2i(170, 390)));
	sprite.setPosition(x, y);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	setObjectSprite(sprite);
}

/*================== setCage =================*/
void Player::setCage(Cage * cage)
{
	m_cage = cage;
}

/*================== rescueFriend =================*/
void Player::rescueFriend()
{
	m_cage->setLiftCage();
}

/*================== pickUpPizza =================*/
void Player::pickUpPizza(Pizza & pizza)
{
	m_state->handleColiisionWithPizza(pizza, *this);
}

/*================== setClimb =================*/
void Player::setClimb(bool val)
{
	m_climb = val;
	if (m_climb)
		m_state = std::make_unique<ClimbingState>(PLAYER_STAND);
}

/*================== isClimb =================*/
bool Player::isClimb()const
{
	return m_climb;
}

/*================== resetPlayer =================*/
void Player::resetPlayer()
{
	m_hearts = MAX_LIVES;
	m_switchBlinkTime = 0.2f;
	m_saltBombsStack = 0;
	m_coins = 0;
	m_pizzas = 0;
	m_frame = 0;
	m_blinks = 0;
	m_dropPizza = true;
	m_isCheesed = false;
	m_collideWithEnemy = false;
	m_climb = false;
	m_pickedPizzaTimer = 0.f;
	m_blinkTimer = sf::seconds(0.f);
	resetGravity();
}