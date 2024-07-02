#pragma region Includes
#include "DesignPatterns/States/PlayerState/BombState.h"
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "DesignPatterns/States/PlayerState/JumpState.h"
#include "DesignPatterns/States/PlayerState/CheesedState.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/MovingSaltBomb.h"
#include "GameObject/MovingObject/Player.h"
#pragma endregion 


/*================== BombState Constructor =================*/
BombState::BombState(const ObjectAnimation animation)
	:PlayerState(animation,sf::seconds(0.1f)),m_XisPressed(true),m_XwasPressed(false)
{
}

/*================== BombState handleEvent =================*/
std::unique_ptr<PlayerState> BombState::handleEvent(Input input, Player& player)
{
	if (!m_XisPressed&& !m_XwasPressed) {
        return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);

	}
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        m_XisPressed = false;
    }
   
	return nullptr;
}

/*================== BombState update =================*/
/*----------------------------------------------------------
player throwing salt bomb, he insert to the list moving salt 
bomb with side to side strategy and manageing key realease with booleans
------------------------------------------------------------*/

void BombState::update(sf::Time elapsed, Player& player)
{
    auto pos = player.getPosition();
    m_saltBomb.setTexture(ResourceManager::instance().getTexture("salt"));
    m_saltBomb.setScale(2.f, 2.f);
    m_saltBomb.setPosition(pos);
    if (player.getSaltBombsAmount() > 0 && !m_XisPressed&& m_XwasPressed)
    {   
        player.createBomb(std::make_unique<MovingSaltBomb>(m_saltBomb, 
            std::make_unique<SideToSideStrategy>(300.f,-4.f), player.isHeadDirectionRight()));
        player.decreaseSaltBombs();
    }
    m_XwasPressed = m_XisPressed;
    
}
