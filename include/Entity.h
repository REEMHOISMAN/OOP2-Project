#pragma once
#include "GameObject.h"

class Entity :public GameObject
{
public:
	Entity(sf::Vector2f& position, sf::Texture& texture);
	void setEntityPosition(sf::Vector2f& Pos);
};