#pragma once
#include <GameStates.h>

class InGameState : public GameStates
{
public:
	InGameState() = default; //just for now..
	virtual void getInput(Input) override {}
	virtual void update() override {}
	virtual void render() override {}

private:
	// will hold entities, Platyer, and all game objects
};