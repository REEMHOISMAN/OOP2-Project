#pragma once
const int WIDTH = 1400;
const int HEIGHT = 800;

const int NUM_OF_TEXTURES = 10;

const float MIN_Y = 560.f;
const float PLAYER_MAX_Y = 300.f;

enum class PlayerStateTypes
{
	STAND,
	WALK,
	RUN,
	JUMP,
	DIVE
};

enum ObjectAnimation
{
	PLAYER_STAND,
	PLAYER_WALK,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_DIVE,
	PLAYER_CHEESED,
	ONION_ENEMY,
	PEPPER_ENEMY,
	ORANGE_ENEMY, 
	PIZZA_ENEMY_MOVE,
	PIZZA_ENEMY_ATTACK,
	PIZZA_ENEMY_DIE
};

using Animation = std::vector<sf::IntRect>;