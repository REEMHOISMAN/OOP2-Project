#pragma once
#include "GameObject/MovingObject/Enemy.h"
#include "GameObject/MovingObject/CheeseBullet.h"

class PizzaEnemyState;
class Level;
class Pizza;

class PizzaEnemy: public Enemy
{
public:
    PizzaEnemy(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy, Level&);
    virtual void move(const sf::Time&) override;
    void createCheese(std::unique_ptr<CheeseBullet> cheese);
    void loadDieState();
    void createPizza(std::unique_ptr<Pizza>);

private:
    static bool m_register;
    std::unique_ptr< PizzaEnemyState> m_state;
    Level& m_game;
};