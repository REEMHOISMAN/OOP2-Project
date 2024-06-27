#pragma once
#include "DesignPatterns/States/GameState/GameState.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/StaticObject/StaticObject.h"
#include "UserInterface.h"
#include "Level.h"
#include <memory>
#include <list>

class GameController;

class InGameState : public GameState
{
public:
	InGameState(GameController&, GameState&);
	virtual void handleEvent(sf::Event&, sf::RenderWindow& window) override;
	virtual void update(sf::Time) override;
	virtual void render(sf::RenderWindow&) override;
	//void insertMovingObject(std::unique_ptr<MovingObject>);
	//void insertStaticObject(std::unique_ptr<StaticObject>);

private:
	//sf::Sprite createNewObjectSprite(float, float, const std::string,float scle=1.f)const;
	//void initTileMap();
	//void drawBoard(sf::RenderWindow&) const;
	//void checkCollision();

	sf::RectangleShape m_background;
	UserInterface m_ui;
	Level m_level;
	/*std::list<std::unique_ptr<MovingObject>> m_movingObjects;
	std::list<std::unique_ptr<StaticObject>> m_staticObjects;*/
	Player m_player;
};

