#include "GameController.h"
#include "Macros.h"
#include "GameStates.h"

GameController::GameController()
	:m_window(sf::VideoMode{WIDTH,HEIGHT},"PAPA LOUIE: WHEN PIZZAS ATTACK")
{
	m_state = &m_inGameState;
	m_window.setFramerateLimit(60);
}

void GameController::run()
{
	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				m_window.close();
			}
		}
	}
}
