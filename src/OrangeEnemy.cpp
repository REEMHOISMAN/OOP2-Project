#include "OrangeEnemy.h"

bool OrangeEnemy::m_register = EnemyFactory::registerEnemy(ORANGE_ENEMY,
	[](auto& sprite, auto&& JumpingStrategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<OrangeEnemy>(sprite, std::move(JumpingStrategy), animation); });