#pragma once
#include "Enemy.h"

class PizzaEnemy: public Enemy
{
public:
    PizzaEnemy(sf::Sprite & sprite, std::unique_ptr<MovingStrategy> strategy, Animation & animation)
        : Enemy(sprite, std::move(strategy), animation) {}
private:
    static bool m_register;
};