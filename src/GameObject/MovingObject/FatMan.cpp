#include "GameObject/MovingObject/FatMan.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

/*================== FatMan Register =================*/
bool FatMan::m_register = MovingObjectFactory::registerMovingObject (sf::Color(3, 38, 196),
	[](float x, float y, Level* level)->std::unique_ptr<Enemy>
	{
		Animation animation = ResourceManager::instance().getAnimation(FAT_MAN_MOVE);
		sf::Sprite sprite(ResourceManager::instance().getTexture("fatPerson"));
		sprite.setTextureRect(animation[0]);
		sprite.setScale(0.7f, 0.7f);
		sprite.setPosition(x, y+30);
		sprite.setOrigin(animation[0].width / 2, animation[0].height / 2);
		return std::make_unique<FatMan>(sprite, std::make_unique<SideToSideStrategy>(OBJECT_SPEED-20.f), animation, *level);
	});

/*================== FatMan Constructor =================*/
FatMan::FatMan(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation animation, Level& level)
	:Enemy(sprite, std::move(strategy)), m_animation(animation), m_animationIndex(-1),
	m_startPosX(sprite.getPosition().x), m_isHappy(false), m_isAngry(false), m_level(level)
{

}

/*================== move =================*/
/**----------------------------------------------
 * the "FatMan" is not moving consistently
 * it moves only when he doesnt have ineraction with the player
   (what make him happy if he has all pizzas / else angry)
 *---------------------------------------------**/

void FatMan::move(const sf::Time& time)
{
	if (m_isAngry || m_isHappy) {
		m_isAngry = false;
		return;
	}
	if (!m_isHappy && !m_isAngry)
	{
		activateGravity(GRAVITY);
		activateStrategy(time);
		loadAnimationFrame(time);
		setOnGround(false);
		setBlockedOnSide(false);
	}
	if (getPosition().x > m_startPosX && isHeadDirectionRight())
	{
		setHeadDirection(false);
		setScale();
	}
	else if (getPosition().x < m_startPosX - 200 && !isHeadDirectionRight())
	{
		setHeadDirection(true);
		setScale();
	}

}

/*================== move =================*/
void FatMan::setIsHappy()
{
	m_animationIndex = -1;
	setTextureRect(ResourceManager::instance().getAnimation(FAT_MAN_HAPPY)[0]);
	m_elapsed = sf::seconds(0.17f);
	m_isHappy = true;
}

/*================== move =================*/
void FatMan::setIsAngry()
{
	m_animationIndex = -1;
	setTextureRect(ResourceManager::instance().getAnimation(FAT_MAN_ANGRY)[0]);
	m_elapsed = sf::seconds(0.17f);
	m_isAngry = true;
}

/*================== move =================*/
bool FatMan::isHappy() const
{
	return m_isHappy;
}

/*================== move =================*/
int FatMan::getTotalPizzas() const
{
	return m_level.levelPizzaAmount();
}

/*================== move =================*/
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
