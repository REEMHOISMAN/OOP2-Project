#pragma once
#include <memory>
#include "Enemy.h"
#include <map>
#include "Macros.h"

using enemyMap = std::map<EnemyType, std::unique_ptr<Enemy>(*)(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&)>;

class EnemyFactory
{
public:
	static std::unique_ptr<Enemy>createSideToSideEnemy(const EnemyType, sf::Sprite&);
	static bool registerEnemy(const EnemyType, std::unique_ptr<Enemy>(*)(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&));

private:
	static enemyMap& getMap()
	{
		static enemyMap map;
		return map;
	}
};