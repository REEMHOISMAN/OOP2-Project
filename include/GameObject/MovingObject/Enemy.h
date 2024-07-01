#pragma once
#include "GameObject/MovingObject/Entity.h"
#include <memory>
#include "Macros.h"

class MovingStrategy;

class Enemy : public Entity
{
public:
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>);
	void activateStrategy(sf::Time);
	void setStrategy(std::unique_ptr<MovingStrategy>);
	static void setEnemySprite(sf::Sprite&, float);


private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
};