#include "States/PlayerState/PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player& player, Input input) : m_player(player), m_input(input), m_gravity{ 0 } {}

Input PlayerState::getInput()const
{
	return m_input;
}
//---------------------------------------------------------
void PlayerState::activateGravity(float gravity)
{
	if (m_player.inJumpState())
		m_gravity += gravity;
}
//---------------------------------------------------------
float PlayerState::getGravity() const
{
	return m_gravity;
}
//---------------------------------------------------------
void PlayerState::setPosition(const sf::Vector2f& pos)
{
	auto sprite = m_player.getObjectSprite();
	
	if ((m_player.isHeadDirectionRight() xor (pos.x > 0)) && pos.x != 0) // so the head will change direction even when he is in the air
	{
		m_player.setOrigin({ sprite.getGlobalBounds().width / 2.f,sprite.getOrigin().y });
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
