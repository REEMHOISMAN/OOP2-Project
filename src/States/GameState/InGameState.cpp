#include "States/GameState/InGameState.h"
#include "ResourceManager.h"
#include "GameCollisions.h"
#include "CollisionHandling.h"
#include "Factories/StaticObjectFactory.h"
#include "Factories/EntityFactory.h"
#include "Macros.h"

InGameState::InGameState()
{
	m_background.setTexture(&ResourceManager::instance().getTexture("background"));
	m_background.setSize({float(WIDTH), float(HEIGHT)});
	m_background.setOrigin(m_background.getSize().x / 2, m_background.getSize().y / 2);
	initTileMap();
	initCollisionFunctions();
}


void InGameState::initTileMap()
{
	auto image = sf::Image();
	float factor_y = 710.f;
	image.loadFromFile("tileMap.png");
	
	for (int y = int(image.getSize().y)-1; y >= 0; y--) // read from the end because print from the begin
	{
		float factor_x = 0.f;
		for (int x = 0; x < int(image.getSize().x); x++)
		{
			auto color = image.getPixel(x, y);
			if (color == sf::Color::Green)
			{
				m_objects.emplace_back(std::move(StaticObjectFactory::createObstacle(factor_x, factor_y, "mainGround")));
			}
			else if (color == sf::Color::Black)
			{
				m_objects.emplace_back(std::move(StaticObjectFactory::createObstacle(factor_x, factor_y, "ground")));
			}
			else if (image.getPixel(x, y) == sf::Color::Red)
			{
				m_entities.emplace_back(std::move(EntityFactory::createPlayer(factor_x)));
			}
			factor_x += 85.f; 
		}
		factor_y -= 90.f; //the height of each texture
	}
}

// for switch to pasue/menu
GameState* InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{
	if (event.type == sf::Event::KeyReleased)
	{
		
	}

	return nullptr;
}

void InGameState::update(sf::Time time)
{
	std::for_each(m_entities.begin(), m_entities.end(), [&time](auto& entity) {entity->move(time); });
	checkCollision();
}

void InGameState::render(sf::RenderWindow&window)
{
	m_background.setPosition(window.getView().getCenter());
	window.draw(m_background);
	drawBoard(window);
}

void InGameState::drawBoard(sf::RenderWindow& window) const
{
	std::for_each(m_entities.cbegin(), m_entities.cend(), [&window](const auto& entity) {entity->draw(window); });
	std::for_each(m_objects.cbegin(), m_objects.cend(), [&window](const auto& object) {object->draw(window); });
}

void InGameState::checkCollision()
{
	for (auto entity1 = m_entities.begin(); entity1 != m_entities.end(); ++entity1)
	{
		for (auto entity2 = entity1+1; entity2!= m_entities.end(); ++entity2)
		{
		
		}
	}

	for (auto entity = m_entities.begin(); entity != m_entities.end(); ++entity)
	{
		for (auto object = m_objects.begin(); object != m_objects.end(); ++object)
		{
			if ((*entity)->isCollide((*object)->getObjectSprite()))
			{
				(*entity)->setCollidenes(true);
				auto func = GameCollisions::instance().CollusionFunc(typeid(**entity), typeid(**object));
				if (func)
				{
					func(*(*entity).get(),*(*object).get());
					break;
				}
			}
			else {
				(*entity)->setCollidenes(false);
			}
		}
	}
}
