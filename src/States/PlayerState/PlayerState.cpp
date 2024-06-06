#include "States/PlayerState/PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player& player, Input input) : m_player(player), m_input(input) {}

Input PlayerState::getInput()const
{
	return m_input;
}
//---------------------------------------------------------
void PlayerState::setPosition(const sf::Vector2f& pos)
{
	auto sprite = m_player.getObjectSprite();
	if (m_player.isHeadDirectionRight() xor (m_input == RIGHT))
	{
		m_player.setOrigin({sprite.getGlobalBounds().width / 2.f,sprite.getOrigin().y});
		m_player.setScale();
		m_player.setHeadDirection();
	}
	m_player.setPosition(pos);

}
//---------------------------------------------------------
sf::Vector2f PlayerState::getPlayerPosition() const
{
	return m_player.getObjectSprite().getPosition();
}
//---------------------------------------------------------
void PlayerState::setAnimation(PlayerStateTypes type, sf::Time time)
{
	m_player.setAnimationRect(type, time);
}
