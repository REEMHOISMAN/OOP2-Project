#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "Macros.h"
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
	PlayerState(const ObjectAnimation type, const sf::Time&);
	virtual ~PlayerState() = default;
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) = 0;
	virtual void update(sf::Time, Player&) = 0;
	virtual void setAnimationFrame(Player& player, sf::Time delta);

private:
	std::vector<sf::IntRect> m_animation;
	sf::Time m_elapsed;
	sf::Time m_animationTimer;
	int m_frame;
};