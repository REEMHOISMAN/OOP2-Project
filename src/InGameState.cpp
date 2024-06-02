#include "InGameState.h"

GameState* InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{
	if (event.type == sf::Event::KeyReleased)
	{
	
	}

	return nullptr;
}

void InGameState::update(sf::Time& dt)
{
	player.move(dt);
}

void InGameState::render(sf::RenderWindow&)
{
	m_player.draw();
}
