#pragma once 
#include"GameObject/StaticObject/StaticObject.h"

class StaticSaltBomb: public StaticObject
{
public:
	StaticSaltBomb(sf::Sprite& sprite);
private:
	static bool m_register;
};