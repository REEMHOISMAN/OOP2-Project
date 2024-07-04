#include "UserInterface.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/Player.h"

/*================== UserInterface =================*/
UserInterface::UserInterface()
{
	m_userInterface.setTexture(&ResourceManager::instance().getTexture("gameFrameBG"));
	m_userInterface.setSize({ static_cast<float>(WIDTH), static_cast<float>(HEIGHT) });
	m_userInterface.setOrigin(m_userInterface.getSize().x / 2.f, m_userInterface.getSize().y / 2.f);
	m_userInterface.setPosition(static_cast<float>(WIDTH / 2), static_cast<float>((HEIGHT / 2)));
}

/*==================showGameInfo =================*/
void UserInterface::showGameInfo(sf::RenderWindow& window, Player& player, int maxPizzas)
{
	m_userInterface.setPosition(window.getView().getCenter());
	window.draw(m_userInterface);
	sf::Text score;

	drawSpriteInfo(window, { window.getView().getCenter().x - 660.f, window.getView().getCenter().y + 290.f }, "papaLoueiHead", 1.8f);
	drawHeartSprites(window, { window.getView().getCenter().x - 550.f, window.getView().getCenter().y + 320.f }, "heart", 2.f, player.getHearts());

	drawSpriteInfo(window,{ window.getView().getCenter().x - 150.f, window.getView().getCenter().y + 300.f }, "salt", 2.5f);
	drawInfo(window, { window.getView().getCenter().x-70.f, window.getView().getCenter().y + 300.f }, player.getSaltBombsAmount());
	
	drawSpriteInfo(window, { window.getView().getCenter().x+140.f, window.getView().getCenter().y + 315.f }, "coin", 2.9f);
	drawInfo(window, { window.getView().getCenter().x + 200.f, window.getView().getCenter().y + 300.f }, player.getCoins());

	drawSpritesPizza(window, { window.getView().getCenter().x + 550.f, window.getView().getCenter().y + 345.f }, 
						"pizza", 2.9f, player.getPizzasAmount(), maxPizzas);

	score.setString(std::to_string(player.getPizzasAmount()) + " / " + std::to_string(maxPizzas));
	score.setPosition(window.getView().getCenter().x + 440.f, window.getView().getCenter().y + 310.f);
	score.setCharacterSize(55);
	score.setOutlineThickness(0.7f);
	score.setStyle(score.Bold);
	score.setFont(ResourceManager::instance().getFont());
	score.setFillColor(sf::Color::White);
	window.draw(score);

}

/*================== showFinelScore =================*/
void UserInterface::showFinelScore(sf::RenderWindow& window, const std::string string, int coins, int level)
{
	sf::Text text;
	text.setString(string);
	text.setPosition(window.getView().getCenter().x -600, window.getView().getCenter().y -205);
	text.setCharacterSize(65);
	text.setLetterSpacing(1.2f);
	text.setOutlineThickness(2.5);
	text.setOutlineColor(sf::Color::Black);
	text.setFont(ResourceManager::instance().getFont(false));
	text.setFillColor(sf::Color::White);
	window.draw(text);

	text.setString("Reached level:  " + std::to_string(level));
	text.setPosition(window.getView().getCenter().x - 600.f, window.getView().getCenter().y - 135.f);
	window.draw(text);

	text.setString("Total Coins:  " + std::to_string(coins) + " x");
	text.setPosition(window.getView().getCenter().x - 600.f, window.getView().getCenter().y-55.f);
	auto sprite = sf::Sprite(ResourceManager::instance().getTexture("coin"));
	sprite.setScale(4.f, 4.f);
	sprite.setPosition(text.getPosition().x + 620.f, text.getPosition().y+12);
	window.draw(text);
	window.draw(sprite);

	text.setString("GAME OVER");
	text.setCharacterSize(85);
	text.setLetterSpacing(2.1f);
	text.setOutlineThickness(3.5f);
	text.setPosition(window.getView().getCenter().x - 600.f, window.getView().getCenter().y + 45.f);
	window.draw(text);
}

/*================== drawSpriteInfo =================*/
void UserInterface::drawSpriteInfo(sf::RenderWindow& window, const sf::Vector2f& pos, const std::string texture, float scaleFactor)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture(texture));
	sprite.setPosition(pos);
	sprite.scale(scaleFactor, scaleFactor);
	window.draw(sprite);
}

/*================== drawInfo =================*/
void UserInterface::drawInfo(sf::RenderWindow& window, const sf::Vector2f& pos, int val)
{
	sf::Text info;
	info.setCharacterSize(55);
	info.setOutlineThickness(0.7f);
	info.setStyle(info.Bold);
	info.setFont(ResourceManager::instance().getFont());
	info.setFillColor(sf::Color::White);
	info.setPosition(window.getView().getCenter().x + 80, window.getView().getCenter().y + 315);
	info.setString("x " + std::to_string(val));
	info.setPosition(pos);
	window.draw(info);
}

/*================== drawHeartSprites =================*/
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

/*================== drawSpritesPizza =================*/
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