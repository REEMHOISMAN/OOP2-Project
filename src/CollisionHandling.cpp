#include "CollisionHandling.h"
#include "GameCollisions.h"
#include "Player.h"
#include "Obstacle.h"
#include "Macros.h"

void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), &playerObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(Obstacle), typeid(Player), &playerObstacle);
}

void playerObstacle(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto pos = player.getObjectSprite().getPosition();
	auto input = player.getUserInput();
	auto newPos = sf::Vector2f();

	player.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);
	if (intersect.height < intersect.width)
	{
		player.exitJumpState();
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