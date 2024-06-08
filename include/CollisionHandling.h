#pragma once
#include <typeinfo>
#include <typeindex>
#include <map>
#include "GameObject.h"

using HitFunctionPtr = void (*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;

class CollisionHandling
{
public:
	static CollisionHandling& instance();
	void addCollusionFunc(const std::type_index, const std::type_index, HitFunctionPtr);
	HitFunctionPtr CollusionFunc(const std::type_index, const std::type_index);

private:
	CollisionHandling(const CollisionHandling&) = delete;
	CollisionHandling& operator=(const CollisionHandling&) = delete;
	CollisionHandling() = default;
	
	void PlayerGroundCollision(GameObject& player, GameObject& ground);

	std::map<Key, HitFunctionPtr> m_collideMap;
};