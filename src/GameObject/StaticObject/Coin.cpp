#include "GameObject/StaticObject/Coin.h"
#include"DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"

bool Coin::m_register = StaticObjectFactory::registerStaticObject(sf::Color(255, 237, 92),
	[](float x, float y)->std::unique_ptr<StaticObject> 
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("coin"));
		sprite.setScale(3.f, 3.f);
		sprite.setPosition(x+20, y + 30);
		return std::make_unique<Coin>(sprite);
	});

Coin::Coin(sf::Sprite& sprite)
	:StaticObject(sprite)
{
}
