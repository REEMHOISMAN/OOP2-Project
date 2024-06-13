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
	if (player.inJumpState() && intersect.height < intersect.width)
	{
		player.exitJumpState();
 		player.setPlayerOnGround(true);
 		newPos.y = -intersect.height+0.2;
	}
	else if (intersect.height < intersect.width)
	{
		newPos.y = -intersect.height;
	}
	if (intersect.height > intersect.width && input == RIGHT)
	{
		newPos.x = -intersect.width;
	}
	if (intersect.height > intersect.width && input == LEFT)
	{
		newPos.x = intersect.width;
	}
	player.setPosition(newPos);
}


void enemyObstacle(GameObject& object1, GameObject& object2)
{
	OnionEnemy& enemy = dynamic_cast<OnionEnemy&>(object1);

	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto newPos = sf::Vector2f();

	enemy.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);
	
	
	
    if (intersect.height > intersect.width)
	{
		newPos.x = intersect.width;
		enemy.setHeadDirection();
		enemy.setScale();

	}
	else if (intersect.height > intersect.width && enemy.isHeadDirectionRight())
	{
		newPos.x = -intersect.width;
		enemy.setHeadDirection();
		enemy.setScale();
	}
	else if (intersect.height < intersect.width)
	{
		newPos.y = -intersect.height;
	}
	enemy.setObjectPosition(enemy.getObjectSprite().getPosition() + newPos);

}