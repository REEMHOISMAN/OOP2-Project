#include "GameObject/MovingObject/Weapon.h"

Weapon::Weapon(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy): MovingObject(sprite), m_moveStrategy(std::move(strategy)){}
