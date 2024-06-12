#pragma once
#include "StaticObject.h"

class Obstacle : public StaticObject
{
public:
	Obstacle(sf::Sprite& sprite) : StaticObject(sprite){}
};