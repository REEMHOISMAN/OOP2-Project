#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Command;

class Button
{
public:
	Button(const sf::IntRect&, Command&);

private:
	sf::RectangleShape m_button;
	Command m_command;
};