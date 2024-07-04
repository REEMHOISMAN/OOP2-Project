#pragma region Includes
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/MovingObject/Player.h"
#pragma endregion 


/*================== CheesedState Constructor =================*/
CheesedState::CheesedState(const ObjectAnimation animation): 
	PlayerState(animation, sf::seconds(0.f)), m_spaceCounter(3), m_pressingOnSpace(false), m_wasPressedOnSpace(true)
{
}

/*================== CheesedState handleEvent =================*/
std::unique_ptr<PlayerState> CheesedState::handleEvent(Input input, Player& player)
{
	if (m_spaceCounter == 0)
	{
		player.setCheesed(false);
		return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);
	}

	if (input == NONE)
		m_pressingOnSpace = false;

	if (input == SPACE)
		m_pressingOnSpace = true;

	return nullptr;
}

/*================== CheesedState update =================*/
/*---------------------------------------------------------
* this state is is when the pizza enemy spit on the player and
* player need to get out of the state by pressing 3 times space
-----------------------------------------------------------*/
void CheesedState::update(sf::Time time, Player& player)
{
	if (!m_pressingOnSpace && m_wasPressedOnSpace)
	{
		--m_spaceCounter;
		setAnimationFrame(player, time);
	}
	
	m_wasPressedOnSpace = m_pressingOnSpace;// manageing key realease with booleans
	
	player.activateGravity(GRAVITY); // if you were jumping -> fall
	
	auto prevPos = player.getPosition();
	prevPos.y += player.getGravity();
	player.setObjectPosition(prevPos);
}
