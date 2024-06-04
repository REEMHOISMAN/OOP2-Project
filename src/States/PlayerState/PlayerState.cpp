#include "States/PlayerState/PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player& player) : m_player(player) {}

void PlayerState::setPosition(const sf::Vector2f& pos)
{
	m_player.setObjectPosition(pos);
}