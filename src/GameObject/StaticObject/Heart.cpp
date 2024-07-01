#include "GameObject/StaticObject/Heart.h"
#include"DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"

/*================== Heart Register =================*/
bool Heart::m_register = StaticObjectFactory::registerStaticObject(sf::Color(136, 0, 21),
	[](float x, float y)->std::unique_ptr<StaticObject>
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("heart"));
		sprite.setScale(2.f, 2.f);
		sprite.setPosition(x, y + 30);
		sprite.setTextureRect(sf::IntRect(36, 5, 24, 24));
		return std::make_unique<Heart>(sprite);
	}
);

/*================== Heart Constructor =================*/
Heart::Heart(sf::Sprite& sprite)
	:StaticObject(sprite)
{
}
