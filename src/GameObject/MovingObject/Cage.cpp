#include "GameObject/MovingObject/Cage.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"

bool Cage::m_register =
MovingObjectFactory::registerMovingObject(sf::Color(127, 127, 127),
	[](float x, float y, InGameState* inGameState)->std::unique_ptr<MovingObject>
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("cage"));
		sprite.setOrigin({ sprite.getGlobalBounds().width / 2,0 });
		sprite.setScale(2.f, 2.f);
		sprite.setPosition(x, -1257);
		sprite.setTextureRect(sf::IntRect(75, 2, 130, 929));
		auto secondRect = sf::IntRect(271, 2, 130, 929);
		return std::make_unique<Cage>(sprite, std::make_unique<UpDownStrategy>(0.f), secondRect);
	});

Cage::Cage(sf::Sprite& sprite, std::unique_ptr<UpDownStrategy> strategy, sf::IntRect& rect):
	MovingObject(sprite),m_strategy(std::move(strategy)), m_liftCage(false), m_unlockedCageRect(rect){}

void Cage::move(sf::Time delta)
{
	if (m_liftCage)
	{
		m_strategy->move(delta, false, 0.f);
	}
}
