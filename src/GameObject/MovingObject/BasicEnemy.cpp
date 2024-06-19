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
	loadAnimationFrame(time);
	setOnGround(false);
	setBlockedOnSide(false);
	
}

void BasicEnemy::loadAnimationFrame(sf::Time deltaTime)
{
	m_elapsed += deltaTime;
	if (m_elapsed.asSeconds() >= 0.3f)
	{
		m_elapsed -= sf::seconds(0.3f);
		++m_animationIndex;
		m_animationIndex %= m_animation.size();
		setTextureRect(m_animation[m_animationIndex]);
	}
}
