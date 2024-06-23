#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Pizza : public StaticObject
{
public:
	Pizza(sf::Sprite& sprite): StaticObject(sprite){}
};