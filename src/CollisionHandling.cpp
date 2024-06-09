#include "CollisionHandling.h"
#include "GameCollisions.h"
#include "Player.h"
#include "Obstacle.h"
#include "Macros.h"

void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), playerObstacle);
}

void playerObstacle(GameObject& object1, GameObject& obstacle)
{
	Player& player= dynamic_cast<Player&>(object1);
	sf::FloatRect intersect;
	auto obstacleSprite = obstacle.getObjectSprite();
	auto pos = player.getObjectSprite().getPosition();
	auto newPos = sf::Vector2f();

	player.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);
	
	if (intersect.height < intersect.width)
	{
		newPos.y = -intersect.height;
	}
	else
	{
		newPos.x = -intersect.width;
	}
	player.setPosition(newPos);
}
