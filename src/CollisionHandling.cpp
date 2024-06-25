#pragma once
#include "CollisionHandling.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/MovingObject/BasicEnemy.h"
#include "GameObject/MovingObject/PizzaEnemy.h"
#include "GameObject/StaticObject/Obstacle.h"
#include "GameObject/StaticObject/StaticSaltBomb.h"
#include "GameObject/StaticObject/Coin.h"
#include "GameObject/StaticObject/Heart.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "GameObject/StaticObject/Pizza.h"
#include <SFML/Audio.hpp>
#include "Macros.h"

//---------------------------------------------------------------------
void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), &playerObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(PizzaEnemy), typeid(Obstacle), &pizzaEnemyFloor);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(StaticSaltBomb), &PlayerStaticBomb);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Heart), &PlayerHeart);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Coin), &PlayerCoins);
	GameCollisions::instance().addCollusionFunc(typeid(MovingSaltBomb), typeid(BasicEnemy), &enemySaltBomb);
	GameCollisions::instance().addCollusionFunc(typeid(PizzaEnemy), typeid(MovingSaltBomb), &pizzaEnemySaltBomb);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(MovingSaltBomb), &enemySaltBomb);
	GameCollisions::instance().addCollusionFunc(typeid(MovingSaltBomb), typeid(Obstacle), &saltBombObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(CheeseBullet), typeid(Obstacle), &cheeseBulletObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(CheeseBullet), &playerCheeseBullet);
	GameCollisions::instance().addCollusionFunc(typeid(CheeseBullet), typeid(Player), &playerCheeseBullet);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(BasicEnemy), &playerEnemy);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Pizza), &playerPizza);
	GameCollisions::instance().addCollusionFunc(typeid(Pizza), typeid(Player), &playerPizza);


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


	if (intersect.height > intersect.width && !enemy.isBlockedFromSide() && enemy.isOnGround()) // collide with wall
	{
		if (enemy.isHeadDirectionRight()) // move from left to right
		{
			enemy.setHeadDirection(false);
			newPos.x = -intersect.width;
		}
		else
		{
			enemy.setHeadDirection(true);
			newPos.x = intersect.width;
		}
		enemy.setBlockedOnSide(true);
		enemy.setScale();
	}
	else if (intersect.height < intersect.width && !enemy.isOnGround())
	{
		newPos.y = -intersect.height;
		enemy.resetGravity();
		enemy.setOnGround(true);
	}

	sf::Vector2f currentPosition = enemy.getObjectSprite().getPosition();
	enemy.setObjectPosition(currentPosition + newPos);
	
}

//---------------------------------
void pizzaEnemyFloor(GameObject& object1, GameObject& object2) 
{
	PizzaEnemy& pizzaEnemy = dynamic_cast<PizzaEnemy&>(object1);
	enemyObstacle(object1, object2);
	pizzaEnemy.setStrategy(std::make_unique<SideToSideStrategy>(220.f));
}

//----------------------------------------------
//colisiion with al the static objects in game- hearts coins salts ...
void PlayerStaticBomb(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	object2.setToErase();
	player.increaseSaltBombs();
	
}
void PlayerHeart(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	object2.setToErase();
	player.increaseHearts();

}
void PlayerCoins(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	object2.setToErase();
	player.increaseCoins();

}

//----------------------------------------------
//colisiion of salt with the ground
void saltBombObstacle(GameObject& object1, GameObject&object2) 
{
	MovingSaltBomb& salt = dynamic_cast<MovingSaltBomb&>(object1);
	sf::FloatRect intersect;
	auto obstacleSprite = object2.getObjectSprite();
	auto newPos = sf::Vector2f();
	salt.getObjectSprite().getGlobalBounds().intersects(obstacleSprite.getGlobalBounds(), intersect);
	/*if (intersect.height > intersect.width) 
	{
		newPos.x = -intersect.width;
		else
		{
			newPos.x = intersect.width;
		}
	}*/
	if (intersect.height < intersect.width)
	{
		newPos.y = -intersect.height;
	}

	//from here logic of second jump when we exit from here we return to side to side strategy
	sf::Vector2f prevPos= salt.getObjectSprite().getPosition();
	if (salt.getJumps()<1) {
		salt.setObjectPosition(prevPos + newPos);
		salt.resetGravity();
		salt.setStrategy(std::make_unique< UpDownStrategy>(5));
		salt.setJumps();
	}
	else if (!salt.isExplode()){
		//salt.setObjectPosition(prevPos+newPos);
		sf::Sprite sprite(ResourceManager::instance().getTexture("explosionSpriteSheet"));
		sprite.setTextureRect(sf::IntRect({ 34,115,116,61 }));
		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
		sprite.setPosition(object2.getObjectSprite().getPosition().x, object2.getObjectSprite().getPosition().y-35);
		salt.setObjectSprite(sprite);
		salt.setExplode();
	}
}


//----------------------------------------------
void cheeseBulletObstacle(GameObject& object1, GameObject& object2)
{
	CheeseBullet& cheese = dynamic_cast<CheeseBullet&>(object1);
	cheese.setToErase();
}

//----------------------------------------------
void playerCheeseBullet(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);

	player.setCheesed(true);
	cheeseBulletObstacle(object2, player); // the cheese will be remove...
}
//-----------------------------------------------
void enemySaltBomb(GameObject& object1, GameObject& object2)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture("explosionSpriteSheet"));
	object1.setToErase();
	MovingSaltBomb& saltBomb = dynamic_cast<MovingSaltBomb&>(object2);
	sprite.setTextureRect(sf::IntRect({ 34,115,116,61 }));
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(object2.getObjectSprite().getPosition());
	saltBomb.setObjectSprite(sprite);
	saltBomb.setExplode();

}

//------------------------------------------------
void pizzaEnemySaltBomb(GameObject& object1, GameObject& object2)
{
	PizzaEnemy& pizzaEnemy = dynamic_cast<PizzaEnemy&>(object1);
	MovingSaltBomb& saltBomb = dynamic_cast<MovingSaltBomb&>(object2);
	sf::Sprite sprite(ResourceManager::instance().getTexture("explosionSpriteSheet"));
	sprite.setTextureRect(sf::IntRect({ 34,115,116,61 }));
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(object1.getObjectSprite().getPosition());
	saltBomb.setObjectSprite(sprite);
	saltBomb.setExplode();
	pizzaEnemy.loadDieState();
}

//------------------------------------------------
void playerEnemy(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	player.setCollideWithEnemy();
}
//------------------------------------------------
void playerPizza(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	Pizza& pizza = dynamic_cast<Pizza&>(object2);
	if (player.GetPizzaTimer()==0.f) {
		player.pickUpPizza(pizza);
	}
	
}
