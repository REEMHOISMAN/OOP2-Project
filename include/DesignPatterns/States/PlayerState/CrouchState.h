#pragma once 
#include "DesignPatterns/States/PlayerState/PlayerState.h"

class Pizza;

class CrouchState :public PlayerState 
{
public:
	CrouchState(const ObjectAnimation animation);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time, Player&) override;
	virtual void handleColiisionWithPizza(Pizza&, Player&)override;

private:
	float m_pizzaHeight;
	bool m_wasPicked;
	bool m_DownWasPressed;
	bool m_stand;
};
