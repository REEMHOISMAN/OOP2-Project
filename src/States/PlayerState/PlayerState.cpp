#include "States/PlayerState/PlayerState.h"
#include "Player.h"
#include "ResourceManager.h"

//load the vector of animation for the relevant state using ResourceManager
//each state's constructor holds its unique ObjectAnimation
PlayerState::PlayerState(const ObjectAnimation type, const sf::Time& animationTimer) : m_frame(0), m_animationTimer(animationTimer),
							m_animation(ResourceManager::instance().getAnimation(type)) {}


void PlayerState::setAnimationFrame(Player& player, sf::Time delta)
{
	m_elapsed += delta;
	if (m_elapsed >= m_animationTimer)
	{
		m_elapsed -= m_animationTimer;
		++m_frame;
		m_frame %= m_animation.size();
		player.setTextureRect(m_animation[m_frame]);
	}
}