#include "States/PlayerState/PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player& player, Input input) : m_player(player), m_input(input) {}

Input PlayerState::getInput()const
{
	return m_input;
}

void PlayerState::setPosition(const sf::Vector2f& pos)
{
	//m_player.setObjectPosition(pos);
	m_player.setPosition(pos);
}