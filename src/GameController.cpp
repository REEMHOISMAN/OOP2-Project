#include "GameController.h"
#include "Macros.h"

GameController::GameController():m_menuState(*this, m_inGameState, m_helpState), m_window(sf::VideoMode{WIDTH,HEIGHT},"PAPA LOUIE: WHEN PIZZAS ATTACK"),
								m_inGameState(*this,m_menuState), m_helpState(*this, m_menuState)
{
	m_state = &m_menuState;
	m_window.setFramerateLimit(60);
}


void GameController::changeState(GameState& state)
{
	m_state = &state;
}

void GameController::run()
{
	sf::Event event;
	sf::Clock clock;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				m_window.close();
			}
			m_state->handleEvent(event, m_window);
		}
		m_state->update(clock.getElapsedTime());
		clock.restart();
		m_window.clear();
		m_state->render(m_window);
		m_window.display();
	}
}
