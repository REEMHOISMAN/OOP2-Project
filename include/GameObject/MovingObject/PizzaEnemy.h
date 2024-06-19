#pragma once
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"
#include "GameObject/MovingObject/CheeseWeapon.h"

class PizzaEnemy: public Enemy
{
public:
    PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy);
    virtual void move(sf::Time) override;
    void increaseJumps();
    void createCheese(std::unique_ptr<CheeseWeapon> cheese);

private:
    static bool m_register;
    float m_WalkTimer;
    int m_jumps;
    std::unique_ptr< PizzaEnemyState> m_state;
};