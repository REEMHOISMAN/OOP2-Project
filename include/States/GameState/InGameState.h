#pragma once
#include "States/GameState/GameState.h"
#include "Player.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include <vector>

class InGameState : public GameState
{
public:
	InGameState();
	virtual GameState* handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;

private:
	sf::Sprite createNewObjectSprite(float, float, const std::string)const;
	void initTileMap();
	void drawBoard(sf::RenderWindow&) const;
	void checkCollision();


	sf::RectangleShape m_background;
	std::vector<std::unique_ptr<MovingObject>> m_movingObjects;
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
};

