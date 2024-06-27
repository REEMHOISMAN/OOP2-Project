#include "GameObject/MovingObject/FatMan.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"

bool FatMan::m_register =MovingObjectFactory::registerMovingObject (sf::Color(3, 38, 196),
	[](float x, float y, InGameState* inGameState)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(FAT_MAN_MOVE);
		sf::Sprite sprite(ResourceManager::instance().getTexture("fatPerson"));
		sprite.setTextureRect(animation[0]);
		sprite.setScale(0.7f, 0.7f);
		sprite.setPosition(x, y);
		return std::make_unique<FatMan>(sprite, std::make_unique<SideToSideStrategy>(200.f), animation);
	});

FatMan::FatMan(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation animation)
	:Enemy(sprite, std::move(strategy)), m_animation(animation), m_animationIndex(-1), m_startPosX(sprite.getPosition().x)
{

}

void FatMan::move(sf::Time time)
{
	activateGravity(0.3f);
	if (getObjectSprite().getPosition().x > m_startPosX )
	{
		setHeadDirection(false);
		setScale();
	}
	else if (getObjectSprite().getPosition().x < m_startPosX - FAT_MAN_OFFSET- 400)
	{
		setHeadDirection(true);
		setScale();
	}
	loadAnimationFrame(time);
	activateStrategy(time);
	setOnGround(false);
	setBlockedOnSide(false);
	
}


void FatMan::loadAnimationFrame(sf::Time deltaTime)
{
	m_elapsed += deltaTime;
	if (m_elapsed.asSeconds() >= 0.17f)
	{
		m_elapsed -= sf::seconds(0.17f);
		++m_animationIndex;
		m_animationIndex %= m_animation.size();
		setTextureRect(m_animation[m_animationIndex]);
	}
}
