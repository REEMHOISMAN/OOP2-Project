#include "DesignPatterns/States/PlayerState/CrouchState.h"
#include "DesignPatterns/States/PlayerState/StandState.h"
#include "GameObject/StaticObject/Pizza.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "GameObject/MovingObject/Player.h"


CrouchState::CrouchState(const ObjectAnimation animation)
	:PlayerState(animation, sf::seconds(0.1f)),m_pizzaHeight(0.f),m_wasPicked(false),m_stand(false)
{
}

std::unique_ptr<PlayerState> CrouchState::handleEvent(Input input, Player& player)
{
	if (input != DOWN||m_stand) {
		player.resetPizzTimer();
		return std::make_unique<StandState>(PLAYER_STAND);
	}
	return nullptr;
}

void CrouchState::update(sf::Time time, Player& player)
{
	if (player.getPizzasAmount() > 0 && !m_wasPicked)
	{
		auto prevPos = player.getObjectSprite().getPosition();
		sf::Sprite sprite(ResourceManager::instance().getTexture("pizza"));
		sprite.setTextureRect(sf::IntRect(42, 0, 42, 10));
		sprite.setPosition(prevPos.x, prevPos.y + player.getObjectSprite().getGlobalBounds().height / 2 - 20);
		sprite.scale(1.7f, 1.7f);
		player.dropPizza(std::make_unique<Pizza>(sprite));
		player.HoldingPizzaTimer(time);
		if (player.GetPizzaTimer() >= 1.f)
			player.resetPizzTimer();
	}
	setAnimationFrame(player, time);
}

void CrouchState::handleColiisionWithPizza(Pizza& pizza, Player& player)
{
	pizza.setToErase();
	player.increasePizza();
	m_wasPicked = true;
}

