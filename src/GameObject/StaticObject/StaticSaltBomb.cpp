#include "GameObject/StaticObject/StaticSaltBomb.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

/*================== StaticSaltBomb Register =================*/
bool StaticSaltBomb::m_register = StaticObjectFactory::registerStaticObject(sf::Color(195, 195, 195),
	[](float x, float y)->std::unique_ptr<StaticObject>
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("salt"));
		sprite.setScale(2.f, 2.f);
		sprite.setPosition(x, y+30);
		return std::make_unique<StaticSaltBomb>(sprite);
	});

/*================== StaticSaltBomb Constructor =================*/
StaticSaltBomb::StaticSaltBomb(sf::Sprite& sprite)
	:StaticObject(sprite)
{
}
