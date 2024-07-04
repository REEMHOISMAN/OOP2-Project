#include "GameObject/MovingObject/Friend.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "Level.h"

/*================== Friend Register =================*/
bool Friend::m_register = MovingObjectFactory::registerMovingObject(sf::Color(47, 225, 17),
	[](float x, float y, Level* level)->std::unique_ptr<MovingObject>
	{
		sf::Sprite sprite(ResourceManager::instance().getTexture("friend")); 
		sprite.setPosition(x, y);
		sprite.setScale(0.3f, 0.3f);
		auto rectPair = std::make_pair(sf::IntRect(243, 184, 275, 478), sf::IntRect(937, 99, 319, 558)); // sad/happy textures
		sprite.setTextureRect(rectPair.first);
		sprite.setOrigin(static_cast<float>(rectPair.first.width / 2), static_cast<float>(rectPair.first.height / 2));
		return std::make_unique<Friend>(sprite, std::make_unique<UpDownStrategy>(0.f), rectPair, *level);
	});

/*================== Friend Constructor =================*/
Friend::Friend(sf::Sprite& sprite, std::unique_ptr<UpDownStrategy> strategy, std::pair<sf::IntRect, sf::IntRect>& rect, Level& level) :
	m_strategy(std::move(strategy)), MovingObject(sprite),
	m_collideWithCageHeight(static_cast<float>(rect.first.height)), m_friendStatusRect(rect),
	m_isHappy(false), m_level(level), m_happyTimer(sf::seconds(3.f))
{}

/*================== move =================*/
/*---------------------------------------------------------
* when the cage being lift up the "friend" gets happy: he's being free.
* the timer here is so the user will see that the "friend" is happy for a bit
* before move to next level
-----------------------------------------------------------*/
void Friend::move(const sf::Time& time)
{
	if (m_isHappy && m_happyTimer.asSeconds() > 0.f) {
		m_happyTimer -= time;
	}
	else if (m_happyTimer.asSeconds() <= 0.f){ 
		m_level.setLevelFinished();
	}
	if (m_isHappy || (!m_isHappy && !isOnGround())) {
		activateGravity(GRAVITY);
		auto pos = m_strategy->move(time, false, getGravity());
		setObjectPosition(getPosition() + pos);
		setOnGround(false);
	}
}

/*================== setHappy =================*/
/*---------------------------------------------------------
* when the cage being lift up the "friend" gets happy: he's being free
-----------------------------------------------------------*/
void Friend::setHappy()
{
	setTextureRect(m_friendStatusRect.second); //set relevant texture rect
	m_isHappy = true;
}

/*================== isHappy =================*/
bool Friend::isHappy() const
{
	return m_isHappy;
}
