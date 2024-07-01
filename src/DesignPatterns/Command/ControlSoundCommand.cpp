#include "DesignPatterns/Command/ControlSoundCommand.h"
#include "GameController.h"

/*================== ControlSoundCommand Constructor =================*/
ControlSoundCommand::ControlSoundCommand(GameController& controller): m_controller(controller)
{
}

/*================== execute =================*/
void ControlSoundCommand::execute()
{
	m_controller.controlSound();
}
