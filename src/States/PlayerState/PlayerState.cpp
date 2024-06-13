#include "States/PlayerState/PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player& player, Input input) : m_player(player), m_input(input), m_gravity(0) {}

Input PlayerState::getInput()const
{
	return m_input;
}

//---------------------------------------------------------
bool PlayerState::playerIsCollide() const
{
	return m_player.getColideData();
}
//---------------------------------------------------------
void PlayerState::activateGravity(float gravity)
{
		m_gravity += gravity;
}
//---------------------------------------------------------
void PlayerState::resetGravity()
{
	m_gravity = 0;
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
	
	if ((m_player.isHeadDirectionRight() != (pos.x > 0)) && pos.x != 0) // so the head will change direction even when he is in the air
	{
		//the problem was because we did sprite.getGlobalBounds() - but when we change animation the texture rect is changing
		m_player.setOrigin({ sprite.getTextureRect().width / 2.f,sprite.getOrigin().y });
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
