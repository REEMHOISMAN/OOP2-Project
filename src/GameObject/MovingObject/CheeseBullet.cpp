#include "GameObject/MovingObject/CheeseBullet.h"

CheeseBullet::CheeseBullet(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy , bool headDirection )
	:Weapon(sprite,std::move(strategy), headDirection)

{
}