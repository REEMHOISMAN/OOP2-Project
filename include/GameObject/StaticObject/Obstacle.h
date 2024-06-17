#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Obstacle : public StaticObject
{
public:
	Obstacle(sf::Sprite& sprite) : StaticObject(sprite){}
};