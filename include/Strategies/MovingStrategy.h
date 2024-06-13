#pragma once 
#include <SFML/Graphics.hpp>

class MovingStrategy
{
public:
	MovingStrategy() = default;
	virtual sf::Vector2f& move(sf::Time,bool,float) = 0;
};