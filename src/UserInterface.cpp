#include "UserInterface.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/Player.h"

UserInterface::UserInterface()
{
	m_userInterface.setTexture(&ResourceManager::instance().getTexture("frameBackground"));
	m_userInterface.setSize({ float(WIDTH), float(HEIGHT) });
	m_userInterface.setOrigin(m_userInterface.getSize().x / 2, m_userInterface.getSize().y / 2);
	m_userInterface.setPosition(WIDTH / 2, HEIGHT / 2);
}

void UserInterface::showGameInfo(sf::RenderWindow& window, Player& player)
{
	m_userInterface.setPosition(window.getView().getCenter());
	window.draw(m_userInterface);
	sf::Sprite sprite(ResourceManager::instance().getTexture("salt"));
	sprite.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 310);
	sprite.scale(2.5f, 2.5f);
	sf::Text score;
	score.setFont(ResourceManager::instance().getFont());
	score.setFillColor(sf::Color::White);
	score.setPosition(window.getView().getCenter().x + 80, window.getView().getCenter().y + 315);
	score.setString("x "+ std::to_string(player.getSaltBombsAmount()));
	score.setCharacterSize(50);
	window.draw(sprite);
	window.draw(score);
}
