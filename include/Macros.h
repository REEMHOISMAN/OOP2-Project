#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

const int WIDTH = 1400;
const int HEIGHT = 800;
const int NUM_OF_TEXTURES = 19;
const int NUM_OF_SOUNDS = 7;
const int MAX_LIVES = 5;
const int MAX_PIZZAS = 3;
const float FAT_MAN_OFFSET = 200.F;
const float MIN_Y = 560.f;
const float PLAYER_MAX_Y = 300.f;//

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
	PLAYER_CROUCH,
	PLAYER_CHEESED,
	PLAYER_STAND_PIZZA,
	PLAYER_WALK_PIZZA,
	PLAYER_RUN_PIZZA,
	PLAYER_JUMP_PIZZA,
	ONION_ENEMY,
	PEPPER_ENEMY,
	ORANGE_ENEMY, 
	PIZZA_ENEMY_MOVE,
	PIZZA_ENEMY_ATTACK,
	PIZZA_ENEMY_DIE,
	FAT_MAN_MOVE,
	FAT_MAN_ANGRY,
	FAT_MAN_HAPPY,
	EXPLOSION
};

using Animation = std::vector<sf::IntRect>;

struct CompareColor
{
	bool operator()(const sf::Color color1, const sf::Color color2)const
	{
		return color1.toInteger() < color2.toInteger();
	}
};