#include "DesignPatterns/States/GameState/HelpState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"

/*================== HelpState  =================*/
/*---------------------------------------------------------
* this state representing two different states "helpStateControls"
* and "helpStateHowToPlay" -> 2 different buttons: "controls"
* and "how to play" both held in the menu (next to each other)
-----------------------------------------------------------*/
HelpState::HelpState(GameController& controller, GameState& state, const std::string background) :
	m_goBackButton(std::make_pair(sf::IntRect(38, 425, 95, 28), sf::IntRect(38, 493, 95, 28)),
		std::make_unique<SwitchScreenCommand>(controller, state), {560.f, 710.f})
{
	m_background.setTexture(&ResourceManager::instance().getTexture(background));
	m_background.setSize({ static_cast<float>(WIDTH), static_cast<float>(HEIGHT) });
	m_background.setOrigin({ static_cast<float>(WIDTH / 2), static_cast<float>(HEIGHT / 2) });
}

/*================== handleEvent  =================*/
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

/*================== handleEvent  =================*/ 
void HelpState::render(sf::RenderWindow& window)
{
	m_background.setPosition(window.getView().getCenter());
	window.draw(m_background);
	m_goBackButton.setPosition({ window.getView().getCenter().x-44.5f, window.getView().getCenter().y +310.f});
	m_goBackButton.draw(window);
}
