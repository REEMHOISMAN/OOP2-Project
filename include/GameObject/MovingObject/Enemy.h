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
	Enemy(sf::Sprite&, std::unique_ptr<MovingStrategy>, Animation&);

protected:
	std::unique_ptr<MovingStrategy> getStrategy();
	void setStrategy(std::unique_ptr<MovingStrategy>);
	void setEnemySprite(sf::Sprite&, float);


private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
};