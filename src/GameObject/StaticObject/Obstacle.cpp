#include "GameObject/StaticObject/Obstacle.h"
#include"DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"

bool Obstacle::m_register = StaticObjectFactory::registerStaticObject(sf::Color::Green, 
	[](float x, float y)->std::unique_ptr<StaticObject> 
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("mainGround"));
		sprite.setPosition(x, y );
		return std::make_unique<Obstacle>(sprite);
	}) 
	&& 
	StaticObjectFactory::registerStaticObject(sf::Color::Black,
	[](float x,float y)->std::unique_ptr<StaticObject> 
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("ground"));
		sprite.setPosition(x, y);
		return std::make_unique<Obstacle>(sprite);
	});
Obstacle::Obstacle(sf::Sprite& sprite)
	:StaticObject(sprite)
{
}
