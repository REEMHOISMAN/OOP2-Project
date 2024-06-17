#include "GameObject/MovingObject/OnionEnemy.h"
#include "Factories/EnemyFactory.h"

bool OnionEnemy::m_register = EnemyFactory::registerEnemy(ONION_ENEMY,
	[](auto& sprite, auto&& sideToSideStrategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<OnionEnemy>(sprite, std::move(sideToSideStrategy), animation); });