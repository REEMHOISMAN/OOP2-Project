#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void handleEvent(sf::Event&,sf::RenderWindow& window) = 0;
	virtual void update(sf::Time) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

};