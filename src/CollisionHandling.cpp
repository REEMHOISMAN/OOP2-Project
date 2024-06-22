#pragma once
#include "CollisionHandling.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/MovingObject/BasicEnemy.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "GameObject/StaticObject/Obstacle.h"
#include "GameObject/StaticObject/StaticSaltBomb.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "Macros.h"

#include <iostream>

//-----------------------------------------------------------------------
void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), &playerObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(PizzaEnemy), typeid(Obstacle), &pizzaEnemyFloor);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(StaticSaltBomb), &PlayerStaticObject);
	GameCollisions::instance().addCollusionFunc(typeid(MovingSaltBomb), typeid(Obstacle), &saltBombObstacale);
}

//-----------------------------------------------------------------------
void playerObstacle(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto playerSprite = player.getObjectSprite();
	auto newPos = sf::Vector2f();

	playerSprite.getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);

		
	if (intersect.height > intersect.width) //collide with wall
	{	
		if (player.isHeadDirectionRight()) {
			newPos.x = -intersect.width;
		}
		else {
			newPos.x = intersect.width;
		}
		player.setBlockedOnSide(true);
	}
	else // collide from above or bottom
	{

		if (playerSprite.getGlobalBounds().top < obstacleSprite.getGlobalBounds().top) //collide with ground
		{  
			newPos.y = -intersect.height;
			player.setOnGround(true);
			player.resetGravity(); //ONLY HERE WE RESET GRAVITY
		}
		else if (playerSprite.getGlobalBounds().top > obstacleSprite.getGlobalBounds().top) //colide from above
		{
			player.setOnGround(true);
			newPos.y = intersect.height;
		}
	}

	sf::Vector2f currentPos = playerSprite.getPosition();
	player.setObjectPosition(currentPos + newPos);
}

//-----------------------------------------------------------------------
void enemyObstacle(GameObject& object1, GameObject& object2)
{

	Enemy& enemy = dynamic_cast<Enemy&>(object1);
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto newPos = sf::Vector2f();

	enemy.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);


	if (intersect.height > intersect.width ) // collide with wall
	{
		if (enemy.isHeadDirectionRight()) // move from left to right
		{
			newPos.x = -intersect.width;
		}
		else
		{
			newPos.x = intersect.width;
		}
		enemy.setBlockedOnSide(true);
		enemy.setHeadDirection(); // collide, so we change direction of its head
		enemy.setScale();
		
	}
	else // collide with ground
	{

		newPos.y = -intersect.height;
		enemy.setOnGround(true);
	
	}

	sf::Vector2f currentPosition = enemy.getObjectSprite().getPosition();
	enemy.setObjectPosition(currentPosition + newPos);
	
}

//---------------------------------
void pizzaEnemyFloor(GameObject& object1, GameObject& object2) 
{
	PizzaEnemy& pizzaEnemy = dynamic_cast<PizzaEnemy&>(object1);
	pizzaEnemy.setStrategy(std::make_unique<SideToSideStrategy>());
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto newPos = sf::Vector2f();

	pizzaEnemy.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);


	if (intersect.height > intersect.width ||  intersect.height > 20.f) // collide with wall
	{
		if (pizzaEnemy.isHeadDirectionRight()) // move from left to right
		{
			newPos.x = -intersect.width;
		}
		else
		{
			newPos.x = intersect.width;
		}
		pizzaEnemy.setBlockedOnSide(true);
		pizzaEnemy.setHeadDirection(); // collide, so we change direction of its head
		pizzaEnemy.setScale();

	}
	else // collide with ground
	{

		newPos.y = -intersect.height;
		pizzaEnemy.setOnGround(true);
		pizzaEnemy.resetGravity();

	}

	sf::Vector2f currentPosition = pizzaEnemy.getObjectSprite().getPosition();
	pizzaEnemy.setObjectPosition(currentPosition + newPos);

	pizzaEnemy.increaseJumps();
}
//colisiion with al the static objects in game- hearts coins salts ...
void PlayerStaticObject(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	sf::FloatRect intersect;
	auto ststicSprite = object2.getObjectSprite();
	auto playerSprite = player.getObjectSprite();
	if (playerSprite.getGlobalBounds().intersects(ststicSprite.getGlobalBounds())) {
		object2.setToErase();
		player.increaseSaltBombs();
	}
}
//colisiion of salt with the ground
void saltBombObstacale(GameObject& object1, GameObject&object2) 
{
	MovingSaltBomb& salt = dynamic_cast<MovingSaltBomb&>(object1);
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto newPos = sf::Vector2f();
	salt.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);


	if (intersect.height > intersect.width) 
	{
		if (salt.isDirectionRight()) 
		{
			newPos.x = -intersect.width;
		}
		else
		{
			newPos.x = intersect.width;
		}
	}
	else 
	{
		newPos.y = -intersect.height;
	}

	//from here logic of second jump when we exit from here we return to side to side strategy
	sf::Vector2f prevPos= salt.getObjectSprite().getPosition();
	if (!salt.toExplode()) {
		auto Jumpspeed=salt.getJumpSpeed();
		sf::Vector2f fixedPos = { newPos.x, Jumpspeed + newPos.y };
		salt.setObjectPosition(prevPos + fixedPos);
		salt.setExplode();
	}
	else
	{
		salt.setToErase();
	}
}