#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"

MenuState::MenuState(GameController& controller, GameState& state)
{
	m_background.setTexture(&ResourceManager::instance().getTexture("menuBackground"));
	m_background.setSize({ WIDTH, HEIGHT });
	m_buttons.emplace_back(std::make_pair(sf::IntRect(42, 35, 166, 34), sf::IntRect(42, 106, 166, 34)), 
											std::make_unique<SwitchScreenCommand>(controller, state));
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
	window.draw(m_background);
	std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) {button.draw(window); });
}

