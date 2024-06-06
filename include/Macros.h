#pragma once
const int WIDTH = 1400;
const int HEIGHT = 800;

const int NUM_OF_TEXTURES = 5;

const float PLAYER_MIN_Y = 590.f;
const float PLAYER_MAX_Y = 300.f;

enum class PlayerStateTypes
{
	STAND,
	WALK,
	RUN,
	JUMP,
	DIVE
};