#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
class Player;

enum Input
{
	NONE, 
	LEFT,
	RIGHT,
	SPACE,
};

class PlayerState
{
public:
	PlayerState(Player& player);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) = 0;
	virtual void update(sf::Time) = 0;
	void setPosition(const sf::Vector2f&);

private:
	Player& m_player;
};