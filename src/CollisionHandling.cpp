#pragma once
#include "CollisionHandling.h"
#include "GameCollisions.h"
#include "Player.h"
#include "Obstacle.h"
#include "Macros.h"
#include "OnionEnemy.h"
#include "PepperEnemy.h"
#include "OrangeEnemy.h"
#include <iostream>

//-----------------------------------------------------------------------
void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), &playerObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(OnionEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(PepperEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(OrangeEnemy), typeid(Obstacle), &enemyObstacle);
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


	if (intersect.height > intersect.width) // collide with wall
	{
		if (enemy.isHeadDirectionRight()) // move from left to right
		{
			newPos.x = -intersect.width;
		}
		else
		{
			newPos.x = intersect.width;
		}
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