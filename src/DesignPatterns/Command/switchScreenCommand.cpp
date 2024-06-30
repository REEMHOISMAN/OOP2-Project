#include "DesignPatterns/Command/SwitchScreenCommand.h"
#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/States/GameState/MenuState.h"
#include "DesignPatterns/States/GameState/GameOverState.h"
#include "GameController.h"


SwitchScreenCommand::SwitchScreenCommand(GameController& controller, GameState& state) :
	m_state(state), m_controller(controller){}

void SwitchScreenCommand::execute()
{
	m_controller.changeState(m_state);
}
