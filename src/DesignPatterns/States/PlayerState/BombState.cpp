#include "DesignPatterns/States/PlayerState/BombState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "GameObject/MovingObject/Player.h"

BombState::BombState(const ObjectAnimation animation)
	:PlayerState(animation,sf::seconds(0.1f)),m_XisPressed(true)
{
}

std::unique_ptr<PlayerState> BombState::handleEvent(Input input, Player& player)
{
	if (!m_XisPressed) {
		return std::make_unique<StandState>(PLAYER_STAND);
	}
    if (input != ATTACK)
    {
        m_XisPressed = false;
    }
   
	return nullptr;
}

void BombState::update(sf::Time elapsed, Player& player)
{
    auto pos = player.getObjectSprite().getPosition();
    player.activateGravity(0.1f);
    m_saltBomb.setTexture(ResourceManager::instance().getTexture("salt"));
    m_saltBomb.setScale(2.f, 2.f);
    m_saltBomb.setPosition(pos);
    if (player.getSaltBombsAmount() > 0 && !m_XisPressed)
    {   

        player.createBomb(std::make_unique<MovingSaltBomb>(m_saltBomb, 
            std::make_unique<SideToSideStrategy>(300.f,-4.f), player.isHeadDirectionRight()));
        player.decreaseSaltBombs();

    }
    
}
