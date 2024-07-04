#include "DesignPatterns/States/GameState/GameOverState.h"
#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameController.h"

/*================== GameOverState constructor =================*/
GameOverState::GameOverState(GameController& controller, GameState& menu, InGameState& inGame):
	m_button(std::make_pair(sf::IntRect(125,557,79,57), sf::IntRect(125,557,79,57)), 
		std::make_unique<SwitchScreenCommand>(controller, menu), {1200.f,650.f}), m_inGame(inGame)
{
	m_background.setTexture(&ResourceManager::instance().getTexture("GameOverBG"));
	m_background.setOrigin(static_cast<float>(WIDTH / 2), static_cast<float>(HEIGHT / 2));
	m_background.setSize({ WIDTH, HEIGHT });
}

/*================== handleEvent =================*/
void GameOverState::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		m_inGame.resetGame();
		m_button.handleClick(pos);
	}

	else if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
		m_button.markButton(pos);
	}
}

/*================== render =================*/
void GameOverState::render(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	m_background.setPosition(window.getView().getCenter());
	window.draw(m_background);
	m_inGame.endGame(window);
	m_button.draw(window);
}
