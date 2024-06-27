#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Obstacle : public StaticObject
{
public:
	Obstacle(sf::Sprite& sprite);
private:
	static bool m_register;
};