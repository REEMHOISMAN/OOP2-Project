#include "CollisionHandling.h"
#include "CollisionHandling.h"
#include "CollisionHandling.h"
#include "CollisionHandling.h"
#include "Obstacle.h"
#include "Player.h"

CollisionHandling& CollisionHandling::instance()
{
	static CollisionHandling instance;
	return instance;
}

void CollisionHandling::addCollusionFunc(const std::type_index object1, const std::type_index object2, HitFunctionPtr func)
{
	m_collideMap[std::make_pair(object1, object2)] = func;
}

HitFunctionPtr CollisionHandling::CollusionFunc(const std::type_index object1, const std::type_index object2)
{
	auto it = m_collideMap.find(std::make_pair(object1, object2));
	//if (it == m_collideMap.end()) //throw exception
	return it->second;
}

void CollisionHandling::PlayerGroundCollision(GameObject& player, GameObject& ground)
{
	player.setObjectPosition({ 0,0 });
}