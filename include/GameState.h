#pragma once
#include <SFML/Graphics.hpp>

//enum Input
//{
//
//};

class GameState
{
public:
	virtual ~GameState() = default;
	virtual GameState* handleEvent(sf::Event&,sf::RenderWindow& window) = 0;
	virtual void update(sf::Time) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	//virtual void init() = 0;
};