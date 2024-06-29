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
	void draw(sf::RenderWindow&);
	void setLevelFinished();
	void resetLevel();
	void inceasePizzaAmount();
	int levelPizzaAmount()const;
	bool isLevelFinished()const;
	
private:
	template<typename T>
	void proccessCollusionWithPlayer(Player& player, T begin, T end);

	template<typename T1, typename T2>
	void processCollisions(T1 begin1, T1 end1, T2 begin2, T2 end2);


	InGameState& m_game;
	std::list<std::unique_ptr<MovingObject>> m_movingObjects;
	std::list<std::unique_ptr<StaticObject>> m_staticObjects;

	int m_pizzas;
	bool m_levelFinish;
	sf::Time m_levelFinishTimer;
	sf::RectangleShape m_loadLevel;
};