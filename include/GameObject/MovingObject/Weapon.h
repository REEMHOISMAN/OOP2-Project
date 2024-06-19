#pragma once
#include "GameObject/MovingObject/MovingObject.h"
#include <memory>

class Weapon : public MovingObject
{
public:
	Weapon(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy);

private:
	std::unique_ptr<MovingStrategy> m_moveStrategy;
};