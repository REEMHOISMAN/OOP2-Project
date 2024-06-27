#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class Coin :public StaticObject
{
public:
	Coin(sf::Sprite& sprite);
private:
	static bool m_register;
};