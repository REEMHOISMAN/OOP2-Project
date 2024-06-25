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
	sf::Sprite sprite;
	sf::Text score;

	drawSpriteInfo(window, { window.getView().getCenter().x - 660, window.getView().getCenter().y + 290 }, "papaLoueiHead", 1.8f);
	drawHeartSprites(window, { window.getView().getCenter().x - 550, window.getView().getCenter().y + 320 }, "heart", 2.f, player.getHearts());

	drawSpriteInfo(window,{ window.getView().getCenter().x - 150, window.getView().getCenter().y + 300 }, "salt", 2.5f);
	drawInfo(window, { window.getView().getCenter().x-70, window.getView().getCenter().y + 300 }, player.getSaltBombsAmount());
	
	drawSpriteInfo(window, { window.getView().getCenter().x+140, window.getView().getCenter().y + 315 }, "coin", 2.9f);
	drawInfo(window, { window.getView().getCenter().x + 200, window.getView().getCenter().y + 300 }, player.getCoins());

	drawSpritesPizza(window, { window.getView().getCenter().x + 550, window.getView().getCenter().y + 345 }, 
						"pizza", 2.9f, player.getPizzasAmount());
}

void UserInterface::drawSpriteInfo(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scaleFactor)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture(texture));
	sprite.setPosition(pos);
	sprite.scale(scaleFactor, scaleFactor);
	window.draw(sprite);
}


void UserInterface::drawInfo(sf::RenderWindow& window, const sf::Vector2f& pos, int val)
{
	sf::Text info;
	info.setCharacterSize(55);
	info.setOutlineThickness(0.7);
	info.setStyle(info.Bold);
	info.setFont(ResourceManager::instance().getFont());
	info.setFillColor(sf::Color::White);
	info.setPosition(window.getView().getCenter().x + 80, window.getView().getCenter().y + 315);
	info.setString("x " + std::to_string(val));
	info.setPosition(pos);
	window.draw(info);
}

void UserInterface::drawHeartSprites(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scaleFactor, int val)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture(texture));
	sprite.scale(scaleFactor, scaleFactor);
	sprite.setTextureRect(sf::IntRect(5, 7, 22, 20));
	float x = pos.x;

	for (int i = 0; i < MAX_LIVES; i++)
	{
		sprite.setPosition(x, pos.y+3);
		window.draw(sprite);
		x += 50.f;
	}

	x = pos.x;
	sprite.setTextureRect(sf::IntRect(36, 5, 24, 24));
	for (int i = 0; i < val; i++)
	{
		sprite.setPosition(x, pos.y);
		window.draw(sprite);
		x += 50.f;
	}

}

//--------------------------------------------------------------------
void UserInterface::drawSpritesPizza(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scaleFactor, int val)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture(texture));
	sprite.setTextureRect(sf::IntRect(0, 0, 41, 10));
	sprite.scale(scaleFactor, scaleFactor);
	float y = pos.y;

	for (int i = 0; i < MAX_PIZZAS; i++)
	{
		sprite.setPosition(pos.x, y);
		window.draw(sprite);
		y -= 23.f;
	}
	
	y = pos.y;
	sprite.setTextureRect(sf::IntRect(42, 0, 42, 10));
	for (int i = 0; i < val; i++)
	{
		sprite.setPosition(pos.x, y);
		window.draw(sprite);
		y -= 23.f;
	}

}