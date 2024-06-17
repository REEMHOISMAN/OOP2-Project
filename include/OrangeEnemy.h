#pragma once
#include "Factories/EnemyFactory.h"
#include "Strategies/UpDownStrategy.h"

class OrangeEnemy : public Enemy
{
public:
    OrangeEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
        : Enemy(sprite, std::move(strategy), animation) {}
private:
    static bool m_register;
};