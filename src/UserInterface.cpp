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

void UserInterface::showGameInfo(sf::RenderWindow& window, Player& player, int maxPizzas)
{
	m_userInterface.setPosition(window.getView().getCenter());
	window.draw(m_userInterface);
	sf::Text score;

	drawSpriteInfo(window, { window.getView().getCenter().x - 660, window.getView().getCenter().y + 290 }, "papaLoueiHead", 1.8f);
	drawHeartSprites(window, { window.getView().getCenter().x - 550, window.getView().getCenter().y + 320 }, "heart", 2.f, player.getHearts());

	drawSpriteInfo(window,{ window.getView().getCenter().x - 150, window.getView().getCenter().y + 300 }, "salt", 2.5f);
	drawInfo(window, { window.getView().getCenter().x-70, window.getView().getCenter().y + 300 }, player.getSaltBombsAmount());
	
	drawSpriteInfo(window, { window.getView().getCenter().x+140, window.getView().getCenter().y + 315 }, "coin", 2.9f);
	drawInfo(window, { window.getView().getCenter().x + 200, window.getView().getCenter().y + 300 }, player.getCoins());

	drawSpritesPizza(window, { window.getView().getCenter().x + 550, window.getView().getCenter().y + 345 }, 
						"pizza", 2.9f, player.getPizzasAmount(), maxPizzas);

	score.setString(std::to_string(player.getPizzasAmount()) + " / " + std::to_string(maxPizzas));
	score.setPosition(window.getView().getCenter().x + 440, window.getView().getCenter().y + 310);
	score.setCharacterSize(55);
	score.setOutlineThickness(0.7);
	score.setStyle(score.Bold);
	score.setFont(ResourceManager::instance().getFont());
	score.setFillColor(sf::Color::White);
	window.draw(score);

}


void UserInterface::showFinelScore(sf::RenderWindow& window, const std::string string, int coins, int level)
{
	sf::Text text;
	text.setString(string);
	text.setPosition(window.getView().getCenter().x -600, /*offset.x*/ window.getView().getCenter().y -205/* + offset.y*/);
	text.setCharacterSize(65);
	text.setLetterSpacing(1.2f);
	text.setOutlineThickness(2.5);
	text.setOutlineColor(sf::Color::Black);
	text.setFont(ResourceManager::instance().getFont(false));
	text.setFillColor(sf::Color::White);
	window.draw(text);

	text.setString("Reached level:  " + std::to_string(level));
	text.setPosition(window.getView().getCenter().x - 600.f, /*offset.x*/ window.getView().getCenter().y - 135.f/* + offset.y*/);
	window.draw(text);

	text.setString("Total Coins:  " + std::to_string(coins) + " x");
	text.setPosition(window.getView().getCenter().x - 600.f, /*offset.x*/ window.getView().getCenter().y-55.f/* + offset.y*/);
	auto sprite = sf::Sprite(ResourceManager::instance().getTexture("coin"));
	sprite.setScale(4.f, 4.f);
	sprite.setPosition(text.getPosition().x + 550.f, text.getPosition().y+12);
	window.draw(text);
	window.draw(sprite);

	text.setString("GAME OVER");
	text.setCharacterSize(85);
	text.setLetterSpacing(2.1f);
	text.setOutlineThickness(3.5f);
	text.setPosition(window.getView().getCenter().x - 600.f, /*offset.x*/ window.getView().getCenter().y + 45.f/* + offset.y*/);
	window.draw(text);
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
void UserInterface::drawSpritesPizza(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scaleFactor, int val, int maxPizzas)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture(texture));
	sprite.setTextureRect(sf::IntRect(0, 0, 41, 10));
	sprite.scale(scaleFactor, scaleFactor);
	float y = pos.y;

	for (int i = 0; i < maxPizzas; i++)
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