#include "States/PlayerState/PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player& player, Input input) : m_player(player), m_input(input) {}

Input PlayerState::getInput()const
{
	return m_input;
}

void PlayerState::setPosition(const sf::Vector2f& pos)
{
	auto prevOrigin = m_player.getObjectSprite().getOrigin();

	if (m_player.isHeadDirectionRight() xor (m_input == RIGHT))
	{
		
		m_player.setScale(-1.f,1.f);
		m_player.setHeadDirection();
	}
	else 
	{
		m_player.setOrigin({ m_player.getObjectSprite().getGlobalBounds().width/2.f,prevOrigin.y});
		m_player.setScale(1.f, 1.f);
	}
	m_player.setPosition(pos);

}