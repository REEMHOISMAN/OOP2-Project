#pragma once
#include "Enemy.h"
#include "EnemyFactory.h"
#include "MovingStrategy.h"

class OnionEnemy : public Enemy
{
private:
	static bool m_register;
};

inline bool OnionEnemy::m_register = EnemyFactory::registerEnemy(ONION_ENEMY,
	[](auto& sprite,auto& sideToSideStrategy, auto& animation)->std::unique_ptr<Enemy>{
		return std::make_unique<OnionEnemy>(sprite, sideToSideStrategy, animation); };)