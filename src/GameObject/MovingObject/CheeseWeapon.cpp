#include "GameObject/MovingObject/CheeseWeapon.h"

CheeseWeapon::CheeseWeapon(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy , bool headDirection )
	:Weapon(sprite,std::move(strategy)),m_rightDirection{headDirection}

{
}

void CheeseWeapon::move(sf::Time)
{
}
