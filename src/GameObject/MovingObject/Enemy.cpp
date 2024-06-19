#include "GameObject/MovingObject/Enemy.h"

Enemy::Enemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation):
	Entity(sprite), m_moveStrategy(std::move(strategy)){}

//---------------------------------------------------
void Enemy::setStrategy(std::unique_ptr<MovingStrategy> strategy)
{
	m_moveStrategy = std::move(strategy);
}

void Enemy::loadAnimation(const ObjectAnimation& enemy)
{
	m_animation = ResourceManager::instance().getAnimation(enemy);
}

void Enemy::loadNewFrame(sf::Time time)
{
	sf::Time animationTime = sf::seconds(0.1f);
	m_elapsed += time;
	if (m_elapsed >= animationTime)
	{
		m_elapsed -= animationTime;
		++m_animationIndex;
		m_animationIndex %= m_animation.size();
		setTextureRect(m_animation[m_animationIndex]);
	}
}

std::unique_ptr<MovingStrategy> Enemy::getStrategy() 
{
	return std::move(m_moveStrategy);
}

//bool Enemy::s_register = Factory::registerIt(ORANGE_ENEMY,
//	[]() { return std::make_unique<Enemy>(std::make_unique<UpDownStrategy>()); }
//	)
//	&&
//	Factory::registerIt(PEPPER_ENEMY,
//		[]() { return std::make_unique<Enemy>(std::make_unique<UpDownStrategy>()); }
//);