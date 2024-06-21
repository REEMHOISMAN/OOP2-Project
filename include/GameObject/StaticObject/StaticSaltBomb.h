#pragma once 
#include"GameObject/StaticObject/StaticObject.h"

class StaticSaltBomb: public StaticObject
{
public:
	StaticSaltBomb(sf::Sprite& sprite) : StaticObject(sprite) {}
};