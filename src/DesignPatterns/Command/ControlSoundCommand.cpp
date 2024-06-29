#include "DesignPatterns/Command/ControlSoundCommand.h"
#include "GameController.h"

ControlSoundCommand::ControlSoundCommand(GameController& controller): m_controller(controller)
{
}

void ControlSoundCommand::execute()
{
	m_controller.controlSound();
}
