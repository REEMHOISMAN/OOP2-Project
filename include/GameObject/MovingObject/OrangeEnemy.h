#pragma once
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"

class OrangeEnemy : public Enemy
{
public:
    OrangeEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
        : Enemy(sprite, std::make_unique<UpDownStrategy>(), animation) {}
private:
    static bool m_register;
};