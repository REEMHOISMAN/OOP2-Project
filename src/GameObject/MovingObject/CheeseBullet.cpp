#include "GameObject/MovingObject/CheeseBullet.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"

/*================== CheeseBullet Constructor =================*/
CheeseBullet::CheeseBullet(sf::Sprite& sprite, std::unique_ptr<MovingStrategy> strategy , bool headDirection )
	:Weapon(sprite,std::move(strategy), headDirection)
{
}