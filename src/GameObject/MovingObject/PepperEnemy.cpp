#include "GameObject/MovingObject/PepperEnemy.h"

bool PepperEnemy::m_register = EnemyFactory::registerEnemy(PEPPER_ENEMY,
	[](auto& sprite, auto&& sideToSideStrategy, auto& animation)->std::unique_ptr<Enemy> {
		return std::make_unique<PepperEnemy>(sprite, std::move(sideToSideStrategy), animation); });