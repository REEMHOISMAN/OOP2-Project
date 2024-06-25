#pragma once
#include "DesignPatterns/Command/Command.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Button
{
public:
	Button(std::pair<sf::IntRect, sf::IntRect>, std::unique_ptr<Command>, const sf::Vector2f);
	void draw(sf::RenderWindow&)const;
	void handleClick(const sf::Vector2f& pos);
	void markButton(const sf::Vector2f& pos);

private:
	sf::RectangleShape m_button;
	std::pair<sf::IntRect, sf::IntRect> m_frames;
	std::unique_ptr<Command> m_command;
};