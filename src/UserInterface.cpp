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
	score.setCharacterSize(55);
	score.setOutlineThickness(0.7);
	score.setStyle(score.Bold);
	score.setFont(ResourceManager::instance().getFont());
	score.setFillColor(sf::Color::White);
	
	score.setPosition(window.getView().getCenter().x + 80, window.getView().getCenter().y + 315);
	score.setString("x "+ std::to_string(player.getSaltBombsAmount()));
	
	window.draw(sprite);
	window.draw(score);
	sprite.setTexture(ResourceManager::instance().getTexture("coin"), true);
	sprite.setPosition(window.getView().getCenter().x-280, window.getView().getCenter().y + 320);
	sprite.scale(1.3, 1.3);
	score.setPosition(window.getView().getCenter().x -200, window.getView().getCenter().y + 315);
	score.setString("x " + std::to_string(player.getCoins()));
	window.draw(sprite);
	window.draw(score);
}
