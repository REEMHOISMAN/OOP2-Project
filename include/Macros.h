#pragma once
const int WIDTH = 1400;
const int HEIGHT = 800;

const int NUM_OF_TEXTURES = 8;

const float PLAYER_MIN_Y = 587.5f;
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
	ONION_ENEMY,
	PEPPER_ENEMY,
	ORANGE_ENEMY, 
	PIZZA_ENEMY
};