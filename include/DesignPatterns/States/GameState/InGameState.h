#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include "GameObject/MovingObject/Player.h"
#include "Button.h"
#include "UserInterface.h"
#include "fstream"
#include "Level.h"
#include <memory>
#include <list>

class GameController;
class GameOverState;

class InGameState : public GameState
{
public:
	InGameState(GameController&, GameOverState&, Button&);
	virtual void handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;
	void readNewLevel();
	void endGame(sf::RenderWindow&);
	void resetGame();
	
private:
	void setView(sf::RenderWindow& window);

	std::ifstream m_playlist;
	sf::RectangleShape m_background;
	sf::RectangleShape m_pause;
	UserInterface m_ui;
	Level m_level;
	Player m_player;
	Button& m_soundButton;
	GameController& m_controller;
	GameOverState& m_gameOver;
	bool m_isPause;
	int m_levelNum;
};

