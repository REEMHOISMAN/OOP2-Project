#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"
#include "DesignPatterns/Command/ControlSoundCommand.h"
#include "Button.h"


MenuState::MenuState(GameController& controller, GameState& InGameState, GameState& helpState, Button& button): m_soundButton(button)
{
	m_background.setTexture(&ResourceManager::instance().getTexture("menuBackground"));
	m_background.setSize({ WIDTH, HEIGHT });
	m_background.setOrigin({ WIDTH / 2, HEIGHT / 2 });
	
	m_buttons.emplace_back(std::make_pair(sf::IntRect(42, 35, 166, 34), sf::IntRect(42, 106, 166, 34)),
						   std::make_unique<SwitchScreenCommand>(controller, InGameState),
						   sf::Vector2f{ 530.f, 250.f });

	m_buttons.emplace_back(std::make_pair(sf::IntRect(36, 304, 118, 23), sf::IntRect(36, 365, 118, 23)),
						   std::make_unique<SwitchScreenCommand>(controller, helpState), 
						   sf::Vector2f{ 530.f, 360.f });

}

void MenuState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		for (auto& button : m_buttons)
		{
			button.handleClick(pos);
		}
		m_soundButton.handleClick(pos);
	}

	else if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
		for (auto& button : m_buttons)
		{
			button.markButton(pos);
		}
	}
	
}

void MenuState::render(sf::RenderWindow&window)
{
	m_background.setPosition(window.getView().getCenter());
	window.draw(m_background);
	m_soundButton.setPosition(window.getView().getCenter());
	m_soundButton.draw(window);
	std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) {button.draw(window); });
}

