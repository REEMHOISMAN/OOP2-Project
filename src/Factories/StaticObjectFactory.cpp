#include "Factories/StaticObjectFactory.h"
#include "ResourceManager.h"
#include <string>

std::unique_ptr<Obstacle> StaticObjectFactory::createObstacle(float x, float y, const std::string filename)
{
	auto sprite = sf::Sprite(ResourceManager::instance().getTexture(filename));
	sprite.setPosition(x, y);
	return std::make_unique<Obstacle>(sprite);
}
