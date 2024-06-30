#include "GameObject/StaticObject/Ladder.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"
#include "DesignPatterns/Singletons/ResourceManager.h"


bool Ladder::m_register=StaticObjectFactory::registerStaticObject(sf::Color(63,31,31),
	[](float x, float y)->std::unique_ptr<StaticObject>
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("ladder"));
		sprite.setTextureRect({ 109, 74, 29, 117 });
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		sprite.scale(2.5f, 2.5f);
		sprite.setPosition(x+30, y-50);
		return std::make_unique<Ladder>(sprite);
	});

Ladder::Ladder(sf::Sprite& sprite)
	:StaticObject(sprite)
{
}
