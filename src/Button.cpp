#include "Button.h"
#include "DesignPatterns/Singletons/ResourceManager.h"

Button::Button(std::pair<sf::IntRect, sf::IntRect> frames, std::unique_ptr<Command> command, const sf::Vector2f pos):
				m_command(std::move(command)), m_frames(frames)
{
	m_button.setTexture(&ResourceManager::instance().getTexture("buttons"));
	m_button.setTextureRect(m_frames.first);
	m_button.setSize({ float(m_frames.first.width*2.5), float(m_frames.first.height*2.5) });
	m_button.setPosition(pos);
}

void Button::draw(sf::RenderWindow&window) const
{
	window.draw(m_button);
}

void Button::handleClick(const sf::Vector2f& pos)
{
	if (m_button.getGlobalBounds().contains(pos))
	{
		m_command->execute();
		m_button.getTextureRect() == m_frames.first ? m_button.setTextureRect(m_frames.second) : m_button.setTextureRect(m_frames.first);
	}
}

void Button::markButton(const sf::Vector2f& pos)
{
	if (m_button.getGlobalBounds().contains(pos))
	{
		m_button.setTextureRect(m_frames.second);
	}
	else {
		m_button.setTextureRect(m_frames.first);
	}
}

void Button::setPosition(const sf::Vector2f& pos)
{
	m_button.setPosition(pos.x + 450.f, pos.y - 330.f);
}
