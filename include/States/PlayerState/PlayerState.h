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
	PlayerState(Player& player, Input);
	virtual ~PlayerState() = default;
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) = 0;
	virtual void update(sf::Time) = 0;
	void activateGravity(float gravity);
	float getGravity()const;
	void setPosition(const sf::Vector2f&);
	sf::Vector2f getPlayerPosition()const;
	void setAnimation(PlayerStateTypes, sf::Time);
	Input getInput() const;


private:
	Player& m_player;
	Input m_input;
	float m_gravity;
	bool m_collide;
};