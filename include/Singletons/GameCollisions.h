#pragma once
#include <typeinfo>
#include <typeindex>
#include <map>
#include "GameObject/GameObject.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/StaticObject/Obstacle.h"

using HitFunctionPtr = void (*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;

class GameCollisions
{
public:
	static GameCollisions& instance();
	void addCollusionFunc(std::type_index, std::type_index, HitFunctionPtr);
	HitFunctionPtr CollusionFunc(const std::type_index&, const std::type_index&);

private:
	GameCollisions(const GameCollisions&) = delete;
	GameCollisions& operator=(const GameCollisions&) = delete;
	GameCollisions() = default;
	
	std::map<Key, HitFunctionPtr> m_collideMap;
};