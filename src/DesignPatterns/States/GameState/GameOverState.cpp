#include "DesignPatterns/States/GameState/GameOverState.h"
#include "GameController.h"
#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

GameOverState::GameOverState(GameController& controller, GameState& state): 
	m_button(std::make_pair(sf::IntRect(125,557,79,57), sf::IntRect(125,557,79,57)), 
		std::make_unique<SwitchScreenCommand>(controller, state), {1200.f,650.f})
{
	m_background.setTexture(&ResourceManager::instance().getTexture("GameOverBG"));
	m_background.setOrigin(WIDTH / 2, HEIGHT / 2);
	m_background.setSize({ WIDTH, HEIGHT });
}

void GameOverState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		m_button.handleClick(pos);
	}

	else if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
		m_button.markButton(pos);
	}
}

void GameOverState::render(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	m_background.setPosition(window.getView().getCenter());
	window.draw(m_background);
	m_button.draw(window);
}
