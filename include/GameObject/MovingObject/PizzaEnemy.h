#pragma once
#include "GameObject/MovingObject/Enemy.h"
#include "DesignPatterns/States/PizzaEnemyStates/PizzaEnemyState.h"
#include "GameObject/MovingObject/CheeseBullet.h"

class InGameState;

class PizzaEnemy: public Enemy
{
public:
    PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, InGameState&);
    virtual void move(sf::Time) override;
    void createCheese(std::unique_ptr<Weapon> cheese);

private:
    static bool m_register;
    std::unique_ptr< PizzaEnemyState> m_state;
    InGameState& m_game;
};