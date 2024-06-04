#include "Player.h"
#include "ResourceManager.h"
#include "StandState.h"
#include "Macros.h"

Player::Player()
{
	m_state = std::make_unique<StandState>(*this);

	m_sprite.setTexture(ResourceManager::instance().getTexture("playerSpriteSheet"));
	
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(165, 45), sf::Vector2i(344, 440)));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(500, 675);
	m_sprite.setScale(0.1f, 0.1f);
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
	auto center = m_sprite.getPosition();
	window.setView(sf::View(center, sf::Vector2f(300, 200)));
	window.draw(m_sprite);
}

void Player::setObjectPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(m_sprite.getPosition() + pos);
}
