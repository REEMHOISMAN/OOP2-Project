#pragma once 

#include "GameObject/StaticObject/StaticObject.h"

class Ladder :public StaticObject
{
public:
	Ladder(sf::Sprite&);
private:
	static bool m_register;
};