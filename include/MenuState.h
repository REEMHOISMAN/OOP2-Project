#pragma once
#include <GameStates.h>

class MenuState : public GameState
{
public:
	InGame() = default; //just for now..
	virtual void getInput(Input) override {}
	virtual void update() override {}
	virtual void render() override {}

private:
	// here we need to think
};