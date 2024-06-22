//#include "UserInterface.h"
//#include "DesignPatterns/Singletons/ResourceManager.h"
//
//UserInterface::UserInterface()
//{
//	m_userInterface.setTexture(&ResourceManager::instance().getTexture("frameBackground"));
//	m_userInterface.setSize({ float(WIDTH), float(HEIGHT) });
//	m_userInterface.setOrigin(m_userInterface.getSize().x / 2, m_userInterface.getSize().y / 2);
//	m_userInterface.setPosition(WIDTH / 2, HEIGHT / 2);
//}
//
//void UserInterface::showGameInfo(sf::RenderWindow& window, int saltBombsNum)const
//{
//	window.draw(m_userInterface);
//	sf::Sprite sprite(ResourceManager::instance().getTexture("salt"));
//	sf::Text score;
//	score.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 300);
//	score.setString("x "+ std::to_string(m_game.getSaltBombsAmount()));
//	//text.setCharacterSize()
//	window.draw(sprite);
//	window.draw(score);
//}
