#pragma region Includes
#include "DesignPatterns/States/PlayerState/CrouchState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/StaticObject/Pizza.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/Player.h"
#include "GameObject/StaticObject/Pizza.h"
#pragma endregion 

/*================== CrouchState Constructor =================*/
CrouchState::CrouchState(const ObjectAnimation animation)
	:PlayerState(animation, sf::seconds(0.f)),m_pizzaHeight(0.f),m_wasPicked(false),m_stand(false), m_DownWasPressed(false)
{
}

/*================== CrouchState handleEvent =================*/
std::unique_ptr<PlayerState> CrouchState::handleEvent(Input input, Player& player)
{
	if (input != DOWN) {
		player.resetPizzTimer();
		return player.getPizzasAmount() == 0 ? std::make_unique<StandState>(PLAYER_STAND) : std::make_unique<StandState>(PLAYER_STAND_PIZZA);
	}
	return nullptr;
}

/*================== CrouchState update =================*/
/*---------------------------------------------------------
* this state is to take pizzas after killing enemy pizza 
* Opening a timer until the next pizza can be taken->Prevents detection 
* of a collision with the pizza straight away when taking down a pizza
-----------------------------------------------------------*/
void CrouchState::update(sf::Time time, Player& player)
{
	if (!player.dropPizza()) {
		player.setDropPizza(true);
		return;
	}
	if (player.getPizzasAmount() > 0 && !m_wasPicked)
	{
		for (int i = 0;i < player.getPizzasAmount();++i)
		{
			auto prevPos = player.getPosition();
			sf::Sprite sprite(ResourceManager::instance().getTexture("pizza"));
			sprite.setTextureRect(sf::IntRect(42, 0, 42, 10));
			sprite.setPosition(prevPos.x, prevPos.y + player.getGlobalBounds().height / 2 - 20-(i*10));
			sprite.scale(1.7f, 1.7f);
			player.insertNewPizza(std::make_unique<Pizza>(sprite));
		}
		player.resetPizzaAmount();
		
		player.HoldingPizzaTimer(time);
		if (player.GetPizzaTimer() >= 1.f)
			player.resetPizzTimer();
	}

	
	setAnimationFrame(player, time);
}

/*================== handleColiisionWithPizza =================*/
void CrouchState::handleColiisionWithPizza(Pizza& pizza, Player& player)
{
	pizza.setToErase();
	player.increasePizza();
	m_wasPicked = true;
}

