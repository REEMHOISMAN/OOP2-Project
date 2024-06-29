#pragma once
#include "DesignPatterns/Command/Command.h"

class GameController;

class ControlSoundCommand : public Command
{
public:
	ControlSoundCommand(GameController&);
	virtual void execute() override;

private:
	GameController& m_controller;
};