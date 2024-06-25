#include "DesignPatterns/States/GameState/HelpState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"

HelpState::HelpState(GameController& controller, GameState& state) :
	m_goBackButton(std::make_pair(sf::IntRect(38, 425, 95, 28), sf::IntRect(38, 493, 95, 28)),
		std::make_unique<SwitchScreenCommand>(controller, state), {560.f, 710.f})
{
	m_background.setTexture(&ResourceManager::instance().getTexture("controls"));
	m_background.setSize({ static_cast<float>(WIDTH), static_cast<float>(HEIGHT) });
}

void HelpState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		m_goBackButton.handleClick(pos);
	}

	else if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
		m_goBackButton.markButton(pos);
	}

}

void HelpState::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	m_goBackButton.draw(window);
}