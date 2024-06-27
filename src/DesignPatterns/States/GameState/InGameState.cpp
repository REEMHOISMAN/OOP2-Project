#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "CollisionHandling.h"

InGameState::InGameState(GameController&controller, GameState& state) : m_level(*this), m_player(m_level)
{
	auto texture = &ResourceManager::instance().getTexture("background");
	m_background.setTexture(texture);
	m_background.setSize({float(WIDTH), float(HEIGHT)});
	m_background.setOrigin(m_background.getSize().x / 2, m_background.getSize().y / 2);
	m_background.setPosition(WIDTH/2, HEIGHT/2);

	sf::Sprite sprite(ResourceManager::instance().getTexture("playerSpriteSheet"));
	m_player.setObjectSprite(sprite);
	
	m_level.readLevelMap("level1.png", m_player);
	initCollisionFunctions();
}


// for switch to pasue/menu
void InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{


}

void InGameState::update(sf::Time time)
{
	m_player.move(time);
	m_level.updateLevel(time, m_player);
}


void InGameState::render(sf::RenderWindow&window)
{
	
	sf::Vector2f viewCenter = window.getView().getCenter();
	int offset = static_cast<int>(viewCenter.x) % static_cast<int>(WIDTH);

	m_background.setPosition(viewCenter.x - offset, HEIGHT / 2);

	window.draw(m_background);

	m_background.setPosition(viewCenter.x - offset + WIDTH, HEIGHT / 2);

	window.draw(m_background);

	m_level.draw(window);
	m_player.draw(window);
	m_ui.showGameInfo(window, m_player);
}
