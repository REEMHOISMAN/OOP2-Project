#pragma once

//need to think about that
enum Input{};

class GameStates
{
public:
	virtual ~GameStates() = default;
	virtual void getInput(Input) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};