#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "CollisionHandling.h"
#include "GameController.h"
#include "Button.h"

//--------------------------------------------------
InGameState::InGameState(GameController& controller ,Button& button) : m_level(*this), m_player(m_level), m_soundButton(button), m_controller(controller)
{
	m_background.setTexture(&ResourceManager::instance().getTexture("background"));
	m_background.setSize({float(WIDTH*3), float(HEIGHT*3)});
	m_background.setOrigin(m_background.getSize().x / 2, m_background.getSize().y / 2);

	m_playlist.open("playlist.txt");

	sf::Sprite sprite(ResourceManager::instance().getTexture("playerSpriteSheet"));
	sprite.scale({ 0.4f, 0.4f });
	m_player.setObjectSprite(sprite);
	
	initCollisionFunctions();
	readNewLevel();
}

//--------------------------------------------------
// for switch to switch to pause/ control sound
void InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		m_soundButton.handleClick(pos);
	}
}

//--------------------------------------------------
void InGameState::update(sf::Time time)
{
	m_player.move(time);
	m_level.updateLevel(time, m_player);
	//if (m_player.getHearts() == 0 ||)      <-------- here we will switch state to "GameOverState" PLAYER IS DEAD
		
}

//--------------------------------------------------
void InGameState::render(sf::RenderWindow&window)
{
	setView(window);

	m_level.draw(window);
	if (m_level.isLevelFinished()) return;

	m_player.draw(window);
	m_ui.showGameInfo(window, m_player, m_level.levelPizzaAmount());
	m_soundButton.setPosition(window.getView().getCenter());
	m_soundButton.draw(window);
}

//--------------------------------------------------
void InGameState::setView(sf::RenderWindow& window)
{
	sf::Vector2f viewCenter = window.getView().getCenter();
	int offset = static_cast<int>(viewCenter.x) % static_cast<int>(WIDTH*3);

	m_background.setPosition(viewCenter.x - offset, HEIGHT/5);
	window.draw(m_background);

	m_background.setPosition(viewCenter.x - offset + 3*WIDTH, HEIGHT/5);
	window.draw(m_background);
}

//--------------------------------------------------
void InGameState::readNewLevel()
{
	m_player.resetPizzaAmount();
	auto levelName = std::string();
	if (std::getline(m_playlist, levelName)) {
		m_level.readLevelMap(levelName, m_player);
	}
	else {                // <--------just for now, here we will ALSO switch state to "GameOverState" NO MORE LEVEL TO READ
		m_controller.close();
	}
}
