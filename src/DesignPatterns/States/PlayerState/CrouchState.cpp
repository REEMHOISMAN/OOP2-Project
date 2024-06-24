#include "DesignPatterns/States/PlayerState/CrouchState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/StaticObject/Pizza.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/Player.h"


CrouchState::CrouchState(const ObjectAnimation animation)
	:PlayerState(animation, sf::seconds(0.1f)),m_pickUpPizza(false), m_DownIsPressed(true)
{
}

std::unique_ptr<PlayerState> CrouchState::handleEvent(Input input, Player& player)
{
	if (input == NONE)
		return std::make_unique<StandState>(PLAYER_STAND);
	if (input != DOWN) {
		m_DownIsPressed = false;
	}
	return nullptr;
}

void CrouchState::update(sf::Time time, Player& player)
{
	//setAnimationFrame();
	
	if (!m_DownIsPressed && player.getPizzasAmount()>0)  
	{
		//setAnimationFrame();
		auto prevPos = player.getObjectSprite().getPosition();
		sf::Sprite sprite(ResourceManager::instance().getTexture("pizza"));
		sprite.setTextureRect(sf::IntRect(42, 0, 42, 10));
		sprite.setPosition(prevPos.x,prevPos.y/2 + player.getObjectSprite().getGlobalBounds().height/2);
		sprite.scale(1.7f, 1.7f);
		player.dropPizza(std::make_unique<Pizza>(sprite));
	}

}
void CrouchState::handleColiisionWithPizza(Pizza& pizza, Player& player)
{
	pizza.setToErase();
	player.increasePizza();
	//m_pickUpPizza = true;

}

