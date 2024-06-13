#pragma once
#include "CollisionHandling.h"
#include "GameCollisions.h"
#include "Player.h"
#include "Obstacle.h"
#include "Macros.h"
#include "OnionEnemy.h"


void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), &playerObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(OnionEnemy), typeid(Obstacle), &enemyObstacle);
}

void playerObstacle(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto input = player.getUserInput();
	auto newPos = sf::Vector2f();

	player.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);
	
	if (intersect.height > intersect.width) {
		if (player.isHeadDirectionRight()) {
			newPos.x = -intersect.width;
		}
		else {
			newPos.x = intersect.width;
		}
	}
	else {
		player.setOnGround(true);
		newPos.y = -intersect.height; 
	}

	sf::Vector2f currentPos = player.getObjectSprite().getPosition();
	player.setObjectPosition(currentPos + newPos);
}


void enemyObstacle(GameObject& object1, GameObject& object2)
{
	OnionEnemy& enemy = dynamic_cast<OnionEnemy&>(object1);

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
		enemy.setOnGround(true);
		newPos.y = -intersect.height;
	}

	sf::Vector2f currentPosition = enemy.getObjectSprite().getPosition();
	enemy.setObjectPosition(currentPosition + newPos);
}