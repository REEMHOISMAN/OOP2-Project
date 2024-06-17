#pragma once
#include "Enemy.h"

class PizzaEnemy: public Enemy
{
public:
    PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Animation& animation);
    virtual void move(sf::Time) override;
    void increaseJumps();
private:
    static bool m_register;
    float m_WalkTimer;
    int m_jumps;
};