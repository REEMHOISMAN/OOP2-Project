#include "GameObject/MovingObject/OrangeEnemy.h"

bool OrangeEnemy::m_register = EnemyFactory::registerEnemy(ORANGE_ENEMY,
	[](auto& sprite, auto&& upDownStrategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<OrangeEnemy>(sprite, std::move(upDownStrategy), animation); });