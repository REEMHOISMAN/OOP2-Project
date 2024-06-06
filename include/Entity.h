#pragma once
#include "GameObject.h"

class Entity :public GameObject
{
public:
	Entity(sf::Sprite&);
	virtual void move(sf::Time) = 0;
};