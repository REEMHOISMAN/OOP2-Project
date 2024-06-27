#include "GameObject/MovingObject/FatMan.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"

bool FatMan::m_register =MovingObjectFactory::registerMovingObject (sf::Color(3, 38, 196),
	[](float x, float y, InGameState* inGameState)->std::unique_ptr<Enemy>
	{
		//Animation animation = ResourceManager::instance().getAnimation(ORANGE_ENEMY);
		sf::Sprite sprite(ResourceManager::instance().getTexture("fatPerson"));
		//sprite.setTextureRect(animation[0]);
		sprite.setScale(0.7f, 0.7f);
		sprite.setPosition(x, y);
		return std::make_unique<FatMan>(sprite, std::make_unique<SideToSideStrategy>(200.f));
	});

FatMan::FatMan(sf::Sprite & sprite, std::unique_ptr<MovingStrategy> strategy)
	:Enemy(sprite,std::move(strategy))
{

}

void FatMan::move(sf::Time time)
{
	activateGravity(0.3f);
	if (getObjectSprite().getPosition().x >FAT_MAN_OFFSET)
	{
		setHeadDirection(false);
	}
	else if (getObjectSprite().getPosition().x < FAT_MAN_OFFSET)
	{
		setHeadDirection(true);
	}
	activateStrategy(time);
	setOnGround(false);
	setBlockedOnSide(false);
}
