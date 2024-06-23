#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/MovingObject/Player.h"

CheesedState::CheesedState(const ObjectAnimation animation): 
	PlayerState(animation, sf::seconds(0.f)), m_spaceCounter(3), m_pressingOnSpace(false), m_wasPressedOnSpace(true)
{
}

//-----------------------------------------
std::unique_ptr<PlayerState> CheesedState::handleEvent(Input input, Player& player)
{
	if (m_spaceCounter == 0)
	{
		player.setCheesed(false);
		return std::make_unique<StandState>(PLAYER_STAND);
	}

	if (input == NONE)
		m_pressingOnSpace = false;

	if (input == SPACE)
		m_pressingOnSpace = true;

	return nullptr;
}

//-----------------------------------------
void CheesedState::update(sf::Time time, Player& player)
{
	if (!m_pressingOnSpace && m_wasPressedOnSpace)
	{
		--m_spaceCounter;
		setAnimationFrame(player, time);
	}
	
	m_wasPressedOnSpace = m_pressingOnSpace;
	
	player.activateGravity(0.3f); // if you were jumping -> fall
	
	auto prevPos = player.getObjectSprite().getPosition();
	prevPos.y += player.getGravity();
	player.setObjectPosition(prevPos);
}
