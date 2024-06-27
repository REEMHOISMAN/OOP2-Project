#pragma once
#include <SFML/Graphics.hpp>

#include <list>

class MovingObject;
class StaticObject;
class InGameState;
class Player;

class Level 
{
public:
	Level(InGameState&);
	void readLevelMap(const std::string, Player&);
	void updateLevel(sf::Time&, Player&);
	void insertMovingObject(std::unique_ptr<MovingObject>);
	void insertStaticObject(std::unique_ptr<StaticObject>);
	void draw(sf::RenderWindow& window) const;


	
private:
	void checkCollision(Player&);

	InGameState& m_game;
	std::list<std::unique_ptr<MovingObject>> m_movingObjects;
	std::list<std::unique_ptr<StaticObject>> m_staticObjects;
};