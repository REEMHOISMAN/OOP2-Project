#pragma once
#include "Factories/EnemyFactory.h"
#include "Strategies/SideToSideStrategy.h"

class OnionEnemy : public Enemy
{
public:
    OnionEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
        : Enemy(sprite, std::move(strategy), animation) {}
private:
    static bool m_register;
};
