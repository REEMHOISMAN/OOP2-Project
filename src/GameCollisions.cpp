#include "GameCollisions.h"
#include "Obstacle.h"
#include "Player.h"

GameCollisions& GameCollisions::instance()
{
	static GameCollisions instance;
	return instance;
}

void GameCollisions::addCollusionFunc(const std::type_index object1, const std::type_index object2, HitFunctionPtr func)
{
	m_collideMap[std::make_pair(object1, object2)] = func;
}

HitFunctionPtr GameCollisions::CollusionFunc(const std::type_index object1, const std::type_index object2)
{
	auto it = m_collideMap.find(std::make_pair(object1, object2));
	if (it == m_collideMap.end()) 
	{
		return nullptr;
	}
	return it->second;
}