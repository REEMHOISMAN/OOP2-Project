#pragma once 
#include "DesignPatterns/States/PlayerState/PlayerState.h"
#include "GameObject/StaticObject/Pizza.h"

class CrouchState :public PlayerState 
{
public:
	CrouchState(const ObjectAnimation animation);
	virtual std::unique_ptr<PlayerState> handleEvent(Input, Player&) override;
	virtual void update(sf::Time, Player&) override;
	virtual void handleColiisionWithPizza(Pizza&, Player&)override;

private:
	float m_pizzaHeight;
	bool m_DownIsPressed;
	bool m_holdingPizza;
};
