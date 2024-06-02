#include "InGameState.h"

// for switch to pasue/menu
GameState* InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{
	if (event.type == sf::Event::KeyReleased)
	{
	
	}

	return nullptr;
}

void InGameState::update(sf::Time dt)
{
	//m_player.move(dt);
}

void InGameState::render(sf::RenderWindow&window)
{
	m_player.draw(window);
}
