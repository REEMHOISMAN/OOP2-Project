#include "Player.h"
#include "ResourceManager.h"
#include "States/PlayerState/StandState.h"
#include "States/PlayerState/WalkState.h"
#include "States/PlayerState/JumpState.h"
#include <iostream>

Player::Player(sf::Sprite& sprite): Entity(sprite), m_rightDirection(false), m_animationIndex(0), m_inJumpState(false)
{
	m_state = std::make_unique<StandState>(*this, NONE);
	
	m_animation[PlayerStateTypes::STAND] = { sf::IntRect(sf::Vector2i(174, 50), sf::Vector2i(170, 390)) };
	m_animation[PlayerStateTypes::JUMP] = { sf::IntRect(sf::Vector2i(627, 50), sf::Vector2i(190, 390)) };
	m_animation[PlayerStateTypes::WALK] = { sf::IntRect(sf::Vector2i(174, 50), sf::Vector2i(170, 390)),
										   sf::IntRect(sf::Vector2i(627, 50), sf::Vector2i(190, 390)) };
	m_animation[PlayerStateTypes::RUN] = { sf::IntRect(sf::Vector2i(1130, 50), sf::Vector2i(170, 390)),
										   sf::IntRect(sf::Vector2i(1600, 50), sf::Vector2i(205, 390)),
										   sf::IntRect(sf::Vector2i(174, 530), sf::Vector2i(170, 390)) };
}

void Player::move(sf::Time time)
{
 	auto input = getUserInput();
	auto state = m_state->handleEvent(input, *this);
	if (state) m_state = std::move(state);
	m_state->update(time);
}

Input Player::getUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_inJumpState = true;
		return SPACE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return LEFT;
	return NONE;
}

void Player::draw(sf::RenderWindow& window)const
{
	auto sprite = getObjectSprite();
	auto center = sf::Vector2f(sprite.getPosition().x, HEIGHT/2);
	window.setView(sf::View(center, sf::Vector2f(WIDTH, HEIGHT)));
	GameObject::draw(window);
}

void Player::setPosition(const sf::Vector2f& pos)
{
	auto sprite = getObjectSprite();
	sf::Vector2f newPos = pos;
 	setObjectPosition(sprite.getPosition() + newPos);
}

void Player::exitJumpState()
{
	m_inJumpState = false;
}



void Player::setAnimationRect(PlayerStateTypes state, sf::Time delta)
{
	sf::Time animationTime;
	state == PlayerStateTypes::RUN ? animationTime = sf::seconds(0.08f) : animationTime = sf::seconds(0.1f);
	m_elapsed += delta;
	if (m_elapsed >= animationTime)
	{
		m_elapsed -= animationTime;
		++m_animationIndex;
		m_animationIndex %= m_animation.find(state)->second.size();
		setTextureRect(m_animation.find(state)->second[m_animationIndex]);
	}
}

bool Player::inJumpState() const
{
	return m_inJumpState;
}
