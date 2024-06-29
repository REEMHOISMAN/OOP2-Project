#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include "GameObject/MovingObject/Player.h"
#include "UserInterface.h"
#include "fstream"
#include "Level.h"
#include <memory>
#include <list>

class Button;
class GameController;

class InGameState : public GameState
{
public:
	InGameState(GameController&, Button&);
	virtual void handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;
	void readNewLevel();
	
private:
	void setView(sf::RenderWindow& window);

	std::ifstream m_playlist;
	sf::RectangleShape m_background;
	UserInterface m_ui;
	Level m_level;
	Player m_player;
	Button& m_soundButton;
	GameController& m_controller;
};

