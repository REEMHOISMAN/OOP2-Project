#include "GameController.h"
#include "Macros.h"

GameController::GameController()
	:m_window(sf::VideoMode{WIDTH,HEIGHT},"PAPA LOUIE: WHEN PIZZAS ATTACK")
{
	m_state = &m_inGameState;
	m_window.setFramerateLimit(60);
}

void GameController::run()
{
	sf::Event event;
	sf::Clock clock;
	while (m_window.isOpen())
	{
		m_window.clear();
		while (m_window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				m_window.close();
			}
			
			auto state = m_state->handleEvent(event, m_window);
			if (state)
			{
				m_state = state;
			}
		}
		m_state->update(clock.getElapsedTime());
		clock.restart();
		m_state->render(m_window);
		m_window.display();
	}
}
