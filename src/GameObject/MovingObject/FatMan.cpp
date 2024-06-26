#include "GameObject/MovingObject/FatMan.h"

FatMan::FatMan(sf::Sprite & sprite, std::unique_ptr<MovingStrategy> strategy,float cageX)
	:Enemy(sprite,std::move(strategy)),m_cageX(cageX)
{

}

void FatMan::move(sf::Time time)
{
	activateGravity(0.3f);
	if (getObjectSprite().getPosition().x > m_cageX + FAT_MAN_OFFSET)
	{
		setHeadDirection(false);
	}
	else if (getObjectSprite().getPosition().x < m_cageX - FAT_MAN_OFFSET)
	{
		setHeadDirection(true);
	}
	activateStrategy(time);
	setOnGround(false);
	setBlockedOnSide(false);
}
