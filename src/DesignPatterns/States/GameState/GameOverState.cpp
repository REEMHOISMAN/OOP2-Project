#include "DesignPatterns/States/GameState/GameOverState.h"
#include "GameController.h"
#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"

GameOverState::GameOverState(GameController& controller, GameState& state): 
	m_button(std::make_pair(sf::IntRect(2,2,155, 113), sf::IntRect(2, 2, 155, 113)), 
		std::make_unique<SwitchScreenCommand>(controller, state), {311.f,222.f}) {}

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

	m_button.draw(window);
}
