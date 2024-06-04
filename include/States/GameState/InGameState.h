#pragma once
#include "States/GameState/GameState.h"
#include "Player.h"
#include <vector>

class InGameState : public GameState
{
public:
	InGameState();
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;

private:
	void initTileMap();
	void drawBoard(sf::RenderWindow&) const;

	Player m_player;
	sf::RectangleShape m_background;
	std::vector<std::vector<sf::Sprite>>m_tileMap;
};