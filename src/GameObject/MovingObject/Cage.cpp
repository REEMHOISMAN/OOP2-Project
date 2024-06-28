#include "GameObject/MovingObject/Cage.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

Cage::Cage(float x, float y): m_liftCage(false), m_cageHeight(0.f)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture("cage"));
	m_cageStatusRect = std::make_pair(sf::IntRect(75, 560, 131, 371), sf::IntRect(267, 560, 131, 371));
	sprite.setPosition(x, y);
	sprite.scale(1.6f, 1.6f);
	setObjectSprite(sprite);
	setTextureRect(m_cageStatusRect.first);
}

void Cage::move(sf::Time delta)
{
	if (m_liftCage && m_cageHeight < MAX_CAGE_HEIGHT)
	{
		auto sprite = getObjectSprite();
		sprite.move({ 0,-1.8f });
		setObjectSprite(sprite);
		m_cageHeight += 1.8f;
	}
}

void Cage::setLiftCage()
{
	m_liftCage = true;
	setTextureRect(m_cageStatusRect.second);
}
