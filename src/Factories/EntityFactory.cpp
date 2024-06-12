#include "Factories/EntityFactory.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Macros.h"

std::unique_ptr<Entity> EntityFactory::createPlayer(float x)
{
	auto sprite = sf::Sprite();
	sprite = sf::Sprite(ResourceManager::instance().getTexture("playerSpriteSheet"));
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(174, 50), sf::Vector2i(170, 390)));
	sprite.scale(0.4f, 0.4f);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(x, PLAYER_MIN_Y);
	return std::make_unique<Player>(sprite);
}
