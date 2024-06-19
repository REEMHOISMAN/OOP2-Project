#include "GameObject/MovingObject/BasicEnemy.h"

BasicEnemy::BasicEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
	:Enemy(sprite,std::move(strategy),animation)
{
}
//---------------------------------------------------------
void BasicEnemy::move(sf::Time time)
{
	if (!isOnGround())
		activateGravity(0.3f);

	else
		resetGravity();

	auto newPos = getStrategy()->move(time, isHeadDirectionRight(), getGravity());

	setObjectPosition(newPos + getObjectSprite().getPosition());
	loadNewFrame(time);
	setOnGround(false);
	setBlockedOnSide(false);
	
}
