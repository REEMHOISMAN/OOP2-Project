#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"
#include "DesignPatterns/Command/ControlSoundCommand.h"
#include "Button.h"

/*================== MenuState constructor =================*/
/*---------------------------------------------------------
* the MenuState gets the: InGameStates, MenuState, HelpStateControls, HelpStateHowToPlay
* those states being pass to the relevant buttonn - in order switch screen by command (to the state)
-----------------------------------------------------------*/
MenuState::MenuState(GameController& controller, GameState& InGameState, GameState& HelpStateControls,
					GameState& HelpStateHowToPlay, Button& button): m_soundButton(button)
{
	m_background.setTexture(&ResourceManager::instance().getTexture("menuBG"));
	m_background.setSize({ WIDTH, HEIGHT });
	m_background.setOrigin({ WIDTH / 2, HEIGHT / 2 });
	
	m_buttons.emplace_back(std::make_pair(sf::IntRect(42, 35, 166, 34), sf::IntRect(42, 106, 166, 34)),
						   std::make_unique<SwitchScreenCommand>(controller, InGameState),
						   sf::Vector2f{ 530.f, 250.f });

	m_buttons.emplace_back(std::make_pair(sf::IntRect(36, 304, 118, 23), sf::IntRect(36, 365, 118, 23)),
						   std::make_unique<SwitchScreenCommand>(controller, HelpStateControls),
						   sf::Vector2f{ 530.f, 360.f });

	m_buttons.emplace_back(std::make_pair(sf::IntRect(36, 176, 171, 26), sf::IntRect(36, 240, 171, 26)),
						   std::make_unique<SwitchScreenCommand>(controller, HelpStateHowToPlay),
						   sf::Vector2f{ 525.f, 455.f });

}

/*================== handleEvent =================*/
/*---------------------------------------------------------
* the events that can happen are - user press on either:
* playButton/soundButton/ on of the other 3 help buttons 
-----------------------------------------------------------*/
void MenuState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		for (auto& button : m_buttons)
		{
			button.handleClick(pos); //check if button was pressed, and handle that case
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

/*================== render =================*/
void MenuState::render(sf::RenderWindow&window)
{
	m_background.setPosition(window.getView().getCenter());
	window.draw(m_background);
	m_soundButton.setPosition({ window.getView().getCenter().x + 450.f, window.getView().getCenter().y - 330.f });
	m_soundButton.draw(window);
	std::for_each(m_buttons.begin(), m_buttons.end(), [&window](auto& button) {button.draw(window); });
}

