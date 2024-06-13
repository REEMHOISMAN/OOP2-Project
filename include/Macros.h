#pragma once
const int WIDTH = 1400;
const int HEIGHT = 800;

const int NUM_OF_TEXTURES = 5;

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

enum EnemyType
{
	ONION_ENEMY
};