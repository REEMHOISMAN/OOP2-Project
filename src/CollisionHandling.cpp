#pragma region Includes
#include "CollisionHandling.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
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
#include "GameObject/MovingObject/FatMan.h"
#include "GameObject/StaticObject/Ladder.h"
#include "GameObject/MovingObject/Cage.h"
#include "GameObject/MovingObject/Friend.h"
#include "Macros.h"
#pragma endregion

/*================== initCollisionFunctions =================*/
void initCollisionFunctions()
{
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Obstacle), &playerObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(FatMan), typeid(Obstacle), &enemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(PizzaEnemy), typeid(Obstacle), &pizzaEnemyObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(StaticSaltBomb), &PlayerStaticBomb);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Heart), &PlayerHeart);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Coin), &PlayerCoins);
	GameCollisions::instance().addCollusionFunc(typeid(PizzaEnemy), typeid(MovingSaltBomb), &pizzaEnemySaltBomb);
	GameCollisions::instance().addCollusionFunc(typeid(BasicEnemy), typeid(MovingSaltBomb), &enemySaltBomb);
	GameCollisions::instance().addCollusionFunc(typeid(MovingSaltBomb), typeid(Obstacle), &saltBombObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(CheeseBullet), typeid(Obstacle), &cheeseBulletObstacle);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(CheeseBullet), &playerCheeseBullet);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(BasicEnemy), &playerEnemy);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(PizzaEnemy), &playerEnemy);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Pizza), &playerPizza);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Pizza), &playerPizza);
	GameCollisions::instance().addCollusionFunc(typeid(Pizza), typeid(Player), &playerPizza);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(FatMan), &playerFatMan);
	GameCollisions::instance().addCollusionFunc(typeid(Player), typeid(Ladder), &playerLadder);
	GameCollisions::instance().addCollusionFunc(typeid(Cage), typeid(Friend), &friendCage);
	GameCollisions::instance().addCollusionFunc(typeid(Friend), typeid(Obstacle), &friendObstacle);


}

/*================== playerObstacle =================*/
void playerObstacle(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	sf::FloatRect intersect;
	auto obstacleBounds = object2.getGlobalBounds();
	auto playerBounds = player.getGlobalBounds();
	auto newPos = sf::Vector2f();

	playerBounds.intersects(obstacleBounds, intersect);

		
	if (intersect.height > intersect.width) //collide with wall
	{
		if (player.isHeadDirectionRight() && playerBounds.left < obstacleBounds.left) {
			newPos.x = -intersect.width;
		}
		else if (!player.isHeadDirectionRight() && playerBounds.left > obstacleBounds.left) {
			newPos.x = intersect.width;
		}
		player.setBlockedOnSide(true);
	}
	else // collide from above or bottom
	{

		if (playerBounds.top < obstacleBounds.top) //collide with ground
		{
			newPos.y = -intersect.height;
			player.setOnGround(true);
			player.resetGravity();
		}
		else if (playerBounds.top > obstacleBounds.top) //colide from above
		{
			newPos.y = intersect.height;
			player.activateGravity(1.f);
		}
	}

	sf::Vector2f currentPos = player.getPosition();
	player.setObjectPosition(currentPos + newPos);
}

/*================== enemyObstacle =================*/
void enemyObstacle(GameObject& object1, GameObject& object2)
{

	Enemy& enemy = dynamic_cast<Enemy&>(object1);
	sf::FloatRect intersect;
	auto obstacleBounds = object2.getGlobalBounds();
	auto enemyBounds = enemy.getGlobalBounds();
	auto newPos = sf::Vector2f();

	enemyBounds.intersects(obstacleBounds, intersect);


	if (intersect.height > intersect.width && 
		!enemy.isBlockedFromSide() && enemy.isOnGround()) 
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
	else if (intersect.height < intersect.width && 
			!enemy.isOnGround() && intersect.top > enemyBounds.top)
	{
		newPos.y = -intersect.height;
		enemy.resetGravity();
		enemy.setOnGround(true);
	}
	else if (intersect.height < intersect.width && 
			!enemy.isOnGround() && intersect.top < enemyBounds.top)
	{
		newPos.y = intersect.height;  // Push enemy down by the height of the intersection
	}

	sf::Vector2f currentPosition = enemy.getPosition();
	enemy.setObjectPosition(currentPosition + newPos);

}

/*================== pizzaEnemyObstacle =================*/
void pizzaEnemyObstacle(GameObject& object1, GameObject& object2)
{
	PizzaEnemy& pizzaEnemy = dynamic_cast<PizzaEnemy&>(object1);
	enemyObstacle(object1, object2);
	pizzaEnemy.setStrategy(std::make_unique<SideToSideStrategy>(OBJECT_SPEED));
}

/*================== PlayerStaticBomb =================*/
void PlayerStaticBomb(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	ResourceManager::instance().playSound("takeSaltSound");

	object2.setToErase();
	player.increaseSaltBombs();
}

/*================== PlayerHeart =================*/
void PlayerHeart(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	object2.setToErase();
	player.increaseHearts();

}

/*================== PlayerCoins =================*/
void PlayerCoins(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	ResourceManager::instance().playSound("coinSound");

	object2.setToErase();
	player.increaseCoins();

}

/*================== saltBombObstacle =================*/
void saltBombObstacle(GameObject& object1, GameObject& object2)
{
	MovingSaltBomb& salt = dynamic_cast<MovingSaltBomb&>(object1);
	sf::FloatRect intersect;
	auto obstacleBounds = object2.getGlobalBounds();
	auto saltBounds = salt.getGlobalBounds();
	auto newPos = sf::Vector2f();

	saltBounds.intersects(obstacleBounds, intersect);
	if (intersect.height < intersect.width)
	{
		newPos.y = -intersect.height;
	}

	sf::Vector2f prevPos = salt.getPosition();
	if (salt.getJumps() < 1) {
		salt.setObjectPosition(prevPos + newPos);
		salt.resetGravity();
		salt.setStrategy(std::make_unique< UpDownStrategy>(5.f));
		salt.setJumps();
	}
	else if (!salt.isExplode())
	{
		sf::Vector2f pos = { object2.getPosition().x, object2.getPosition().y - 35 };
		auto sprite = proccessExplotion(pos);
		salt.setObjectSprite(sprite);
		salt.setExplode();
	}
}

/*================== cheeseBulletObstacle =================*/
void cheeseBulletObstacle(GameObject& object1, GameObject& object2)
{
	CheeseBullet& cheese = dynamic_cast<CheeseBullet&>(object1);
	cheese.setToErase();
}

/*================== playerCheeseBullet =================*/
void playerCheeseBullet(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);

	player.setCheesed(true);
	cheeseBulletObstacle(object2, player);
}

/*================== enemySaltBomb =================*/
void enemySaltBomb(GameObject& object1, GameObject& object2)
{
	MovingSaltBomb& saltBomb = dynamic_cast<MovingSaltBomb&>(object2);
	if (saltBomb.isExplode())return;
	auto pos = object2.getPosition();
	auto sprite = proccessExplotion(pos);
	saltBomb.setObjectSprite(sprite);
	saltBomb.setExplode();
	object1.setToErase();
}

/*================== pizzaEnemySaltBomb =================*/
void pizzaEnemySaltBomb(GameObject& object1, GameObject& object2)
{
	PizzaEnemy& pizzaEnemy = dynamic_cast<PizzaEnemy&>(object1);
	MovingSaltBomb& saltBomb = dynamic_cast<MovingSaltBomb&>(object2);
	if (saltBomb.isExplode())return;
	auto pos = pizzaEnemy.getPosition();
	auto sprite = proccessExplotion(pos);
	saltBomb.setObjectSprite(sprite);
	saltBomb.setExplode();
	pizzaEnemy.loadDieState();

}

/*================== playerEnemy =================*/
void playerEnemy(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	player.setCollideWithEnemy();
}

/*================== playerPizza =================*/
void playerPizza(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	Pizza& pizza = dynamic_cast<Pizza&>(object2);
	player.setDropPizza(false);
	if (player.GetPizzaTimer() == 0.f) {
		player.pickUpPizza(pizza);
	}
}

/*================== playerFatMan =================*/
void playerFatMan(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	FatMan& fatMan = dynamic_cast<FatMan&>(object2);
	sf::FloatRect intersect;
	auto fatManBounds = fatMan.getGlobalBounds();
	auto playerBounds = player.getGlobalBounds();
	auto newPos = sf::Vector2f();

	playerBounds.intersects(fatManBounds, intersect);


	if (intersect.height > intersect.width && !fatMan.isHappy())
	{
		if (fatMan.isHeadDirectionRight()) {
			fatMan.setHeadDirection(false);
			fatMan.setScale();
		}
		if (player.getPizzasAmount() != fatMan.getTotalPizzas()) {
			fatMan.setIsAngry();
		}
		else {
			player.resetPizzaAmount();
			fatMan.setIsHappy();
			player.rescueFriend();
		}
	}

	sf::Vector2f currentPos = player.getPosition();
	player.setObjectPosition(currentPos + newPos);
}

/*================== playerLadder =================*/
void playerLadder(GameObject& object1, GameObject& object2)
{
	Player& player = dynamic_cast<Player&>(object1);
	Ladder& ladder = dynamic_cast<Ladder&>(object2);
	sf::FloatRect intersect;
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !player.isClimb()) return;

	auto playerBounds = player.getGlobalBounds();
	auto ladderBounds = ladder.getGlobalBounds();
	auto newPos = sf::Vector2f();
	
	playerBounds.intersects(ladderBounds, intersect);

	if (intersect.width > ladderBounds.width / 1.5 &&
		playerBounds.top > ladderBounds.top - playerBounds.height/2)
	{
		player.setClimb(true);
	}
}

/*================== friendCage =================*/
void friendCage(GameObject& object1, GameObject& object2)
{
	Friend& pal = dynamic_cast<Friend&>(object2);

	sf::FloatRect intersect;
	auto palBounds = pal.getGlobalBounds();
	auto cageBounds = object1.getGlobalBounds();
	auto newPos = sf::Vector2f();

	palBounds.intersects(cageBounds, intersect);

	if (intersect.height+10 < pal.getTextureRect().height * 0.3f-10 
		&& !pal.isHappy() && pal.isOnGround()) {
		pal.setHappy();
	}
}

/*================== friendObstacle =================*/
void friendObstacle(GameObject& object1, GameObject& object2)
{
	Friend& pal = dynamic_cast<Friend&>(object1);

	sf::FloatRect intersect;
	auto palBounds = pal.getGlobalBounds();
	auto obstacleBounds = object2.getGlobalBounds();
	auto newPos = sf::Vector2f();

	palBounds.intersects(obstacleBounds, intersect);

	newPos.y = -intersect.height;
	pal.resetGravity();
	pal.setOnGround(true);
}

/*================== proccessExplotion =================*/
sf::Sprite& proccessExplotion(const sf::Vector2f& pos)
{
	sf::Sprite sprite(ResourceManager::instance().getTexture("explosionSpriteSheet"));
	sprite.setTextureRect(sf::IntRect({ 34,115,116,61 }));
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	sprite.setPosition(pos);
	return sprite;
}