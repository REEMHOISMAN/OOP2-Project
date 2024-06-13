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
	PlayerState() = default;
	virtual ~PlayerState() = default;
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) = 0;
	virtual void update(sf::Time, Player&) = 0;
};