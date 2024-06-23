#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Heart :public StaticObject 
{
public:
	Heart(sf::Sprite& sprite) :StaticObject(sprite){}
};