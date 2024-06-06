#pragma once
const int WIDTH = 1400;
const int HEIGHT = 800;

const int NUM_OF_TEXTURES = 5;

const float PLAYER_MIN_Y = 800.f;

enum class PlayerStateTypes
{
	STAND,
	WALK,
	RUN,
	JUMP,
	DIVE
};