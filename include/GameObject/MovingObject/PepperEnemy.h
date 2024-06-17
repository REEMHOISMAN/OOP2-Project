#pragma once
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

class PepperEnemy : public Enemy
{
public:
    PepperEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation)
        : Enemy(sprite, std::move(strategy), animation) {}
private:
    static bool m_register;
};
