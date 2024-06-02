#include "Player.h"

Player::Player()
{
	m_texture.loadFromFile("playerSpriteSheet.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition({ 20.,20 });
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
