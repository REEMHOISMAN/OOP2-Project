#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/PizzaEnemy.h"

PizzaEnemyState::PizzaEnemyState(const ObjectAnimation animation): m_animation(ResourceManager::instance().getAnimation(animation)), m_frame(0)
{}
void PizzaEnemyState::setAnimationFrame(PizzaEnemy& player, sf::Time delta)
{
	m_elapsed += delta;
	if (m_elapsed >= sf::seconds(0.3f))
	{
		m_elapsed -= sf::seconds(0.3f);
		++m_frame;
		m_frame %= m_animation.size();
		player.setTextureRect(m_animation[m_frame]);
	}
}