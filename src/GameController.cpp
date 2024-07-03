#include "GameController.h"
#include "Macros.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/ControlSoundCommand.h"

GameController::GameController(): m_soundButton(std::make_pair(sf::IntRect(79, 576, 17, 13),
												sf::IntRect(44, 576, 21, 13)),
												std::make_unique<ControlSoundCommand>(*this),
												sf::Vector2f{ 1150.f, 70.f }), 
								  m_menuState(*this, m_inGameState, m_helpStateControls, m_helpStateHowToPlay, m_soundButton),
								  m_window(sf::VideoMode{WIDTH,HEIGHT}, "PAPA LOUIE: WHEN PIZZAS ATTACK"),
								  m_inGameState(*this, m_gameOver, m_soundButton),
								  m_helpStateControls(*this, m_menuState, "controls"),
								  m_helpStateHowToPlay(*this, m_menuState, "howToPlay"),
								  m_gameOver(*this, m_menuState, m_inGameState)
								
{
	m_state = &m_menuState;
	m_window.setFramerateLimit(60);
	m_music.openFromFile("papaLoueiSong.ogg");
	m_music.setLoop(true);
	m_music.play();
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

void GameController::controlSound()
{
	if (m_music.getStatus() == sf::Music::Status::Playing)
	{
		m_music.pause();
	}
	else
	{
		m_music.play();
	}
	ResourceManager::instance().setSoundStatus();
}

void GameController::close()
{
	m_window.close();
}
