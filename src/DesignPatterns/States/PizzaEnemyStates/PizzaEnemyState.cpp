#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/PizzaEnemy.h"

PizzaEnemyState::PizzaEnemyState(const ObjectAnimation animation, const sf::Time frameTimer) :
	m_animation(ResourceManager::instance().getAnimation(animation)), m_animationTime(frameTimer), m_frame(0)
{}

bool PizzaEnemyState::setAnimationFrame(PizzaEnemy& pizzaEnemy, sf::Time delta)
{
	m_elapsed += delta;
	if (m_elapsed >= m_animationTime)
	{
		m_elapsed -= m_animationTime;
		++m_frame;
		m_frame %= m_animation.size();
		pizzaEnemy.setTextureRect(m_animation[m_frame]);
	}
	return m_frame == m_animation.size() - 1;
}