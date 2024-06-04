#include "Player.h"
#include "ResourceManager.h"
#include "States/PlayerState/StandState.h"
#include "Macros.h"

Player::Player()
{
	m_state = std::make_unique<StandState>(*this);

	m_sprite.setTexture(ResourceManager::instance().getTexture("playerSpriteSheet"));
	
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(165, 45), sf::Vector2i(344, 440)));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(700, 645);
	m_sprite.scale(0.4f, 0.4f);
}

void Player::move(sf::Time time)
{
	auto input = getInput();
	//m_state = m_state->handleEvent(input, *this);
	m_state->update(time);
}

Input Player::getInput() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return SPACE;
}

void Player::draw(sf::RenderWindow& window) const
{
	auto center = sf::Vector2f(m_sprite.getPosition().x, HEIGHT/2);
	window.setView(sf::View(center, sf::Vector2f(WIDTH, HEIGHT)));
	window.draw(m_sprite);
}

void Player::setObjectPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(m_sprite.getPosition() + pos);
}
