#include "Player.h"

Player::Player()
{
	m_texture.loadFromFile("playerSpriteSheet.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect({ 160, 30, 230, 430 });
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(90, 550);
	m_sprite.setScale(0.3f, 0.3f);
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
