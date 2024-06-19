#pragma once
#include "GameObject/MovingObject/Entity.h"
#include "vector"
#include "DesignPatterns/Strategies/MovingStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include <memory>
#include "Macros.h"



class Enemy : public Entity
{
public:
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>);
	virtual void move(sf::Time) = 0;

protected:
	void activateStrategy(sf::Time);
	void setStrategy(std::unique_ptr<MovingStrategy>);
	static void setEnemySprite(sf::Sprite&, float);


private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
};