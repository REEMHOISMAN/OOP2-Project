#include "GameObject/MovingObject/FatMan.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"

bool FatMan::m_register =MovingObjectFactory::registerMovingObject (sf::Color(3, 38, 196),
	[](float x, float y, Level* )->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(FAT_MAN_MOVE);
		sf::Sprite sprite(ResourceManager::instance().getTexture("fatPerson"));
		sprite.setTextureRect(animation[0]);
		sprite.setScale(0.7f, 0.7f);
		sprite.setPosition(x, y);
		sprite.setOrigin(animation[0].width / 2, animation[0].height / 2);
		return std::make_unique<FatMan>(sprite, std::make_unique<SideToSideStrategy>(200.f), animation);
	});

FatMan::FatMan(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation animation)
	:Enemy(sprite, std::move(strategy)), m_animation(animation), m_animationIndex(-1),
	m_startPosX(sprite.getPosition().x), m_isHappy(false), m_isAngry(false)
{

}

void FatMan::move(sf::Time time)
{
	if (!m_isHappy && !m_isAngry)
	{
		activateGravity(0.3f);
		activateStrategy(time);
		loadAnimationFrame(time);
		setOnGround(false);
		setBlockedOnSide(false);
	}
	else if (getObjectSprite().getPosition().x > m_startPosX && isHeadDirectionRight())
	{
		setHeadDirection(false);
		setScale();
	}
	else if (getObjectSprite().getPosition().x < m_startPosX - FAT_MAN_OFFSET- 400 && !isHeadDirectionRight())
	{
		setHeadDirection(true);
		setScale();
	}

	m_isHappy = false;
	m_isAngry = false;
}

//------------------------------------
void FatMan::setIsHappy()
{
	m_animationIndex = -1;
	setTextureRect(ResourceManager::instance().getAnimation(FAT_MAN_HAPPY)[0]);
	m_isHappy = true;
}
//------------------------------------
void FatMan::setIsAngry()
{
	m_animationIndex = -1;
	setTextureRect(ResourceManager::instance().getAnimation(FAT_MAN_ANGRY)[0]);
	m_isAngry = true;
}

//------------------------------------
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
