#pragma once
#include "DesignPatterns/Command/Command.h"

class GameController;
class GameState;

class SwitchScreenCommand : public Command
{
public:
	SwitchScreenCommand(GameController&, GameState&);
	virtual void execute();

private:
	GameController& m_controller;
	GameState& m_state;
};