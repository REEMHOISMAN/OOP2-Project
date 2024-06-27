#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "CollisionHandling.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"
#include "GameObject/StaticObject/StaticSaltBomb.h"
#include "GameObject/StaticObject/Heart.h"
#include "GameObject/StaticObject/Coin.h"
#include "GameObject/MovingObject/CheeseBullet.h"
#include "GameObject/MovingObject/Cage.h"
#include "GameObject/MovingObject/FatMan.h"
#include "DesignPatterns/Strategies/UpDownStrategy.h"
#include "DesignPatterns/Strategies/SideToSideStrategy.h"
#include "Macros.h"
#include "GameController.h"
#include <algorithm>

InGameState::InGameState(GameController&controller, GameState& state) : m_player(*this)
{
	auto texture = &ResourceManager::instance().getTexture("background");
	m_background.setTexture(texture);
	m_background.setSize({float(WIDTH), float(HEIGHT)});
	m_background.setOrigin(m_background.getSize().x / 2, m_background.getSize().y / 2);
	m_background.setPosition(WIDTH/2, HEIGHT/2);
	
	initTileMap();
	initCollisionFunctions();
}

//----------------------------------------------------------
void InGameState::initTileMap()
{
	auto image = sf::Image();
	float factor_y = 620.f; 
	image.loadFromFile("tileMap.png");
	sf::Sprite sprite;
	float cageCenterX;
	for (int y = int(image.getSize().y)-1; y >= 0; y--) // read from the end because print from the begin
	{
		float factor_x = 0.f;
		for (int x = 0; x < int(image.getSize().x); x++)
		{
			auto color = image.getPixel(x, y);
			if (color == sf::Color::Green)
			{
				sprite = createNewObjectSprite(factor_x, factor_y, "mainGround");
				m_staticObjects.emplace_back(std::make_unique<Obstacle>(sprite));
			}
			else if (color == sf::Color::Black)
			{
				sprite = createNewObjectSprite(factor_x, factor_y, "ground");
				m_staticObjects.emplace_back(std::make_unique<Obstacle>(sprite));
			}
			else if (image.getPixel(x, y) == sf::Color::Red)
			{
				sprite = createNewObjectSprite(factor_x, 300, "playerSpriteSheet");
				sprite.setTextureRect(sf::IntRect(sf::Vector2i(174, 50), sf::Vector2i(170, 390)));
				sprite.scale(0.4f, 0.4f);
				sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
				m_player.setObjectSprite(sprite);
			}
			else if (auto movingObject = MovingObjectFactory::createMovingObject(color, factor_x, 300, this))
			{
				m_movingObjects.emplace_back(std::move(movingObject));
			}
			else if (auto staticObject = StaticObjectFactory::createStaticObject(color, factor_x, factor_y)) 
			{
				m_staticObjects.emplace_back(std::move(staticObject));
			}
			else if (image.getPixel(x, y) == sf::Color(195, 195, 195))
			{
				sprite = createNewObjectSprite(factor_x, MIN_Y, "salt",2.f);
				sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
				m_staticObjects.emplace_back(std::make_unique<StaticSaltBomb>(sprite));
			}
			else if (image.getPixel(x, y) == sf::Color(136, 0, 21))
			{
				sprite = createNewObjectSprite(factor_x, factor_y+30, "heart", 2.f);
				sprite.setTextureRect(sf::IntRect(36, 5, 24, 24));
				m_staticObjects.emplace_back(std::make_unique<Heart>(sprite));
			}
			else if (image.getPixel(x, y) == sf::Color(255, 237, 92))
			{
				sprite = createNewObjectSprite(factor_x, factor_y+30, "coin", 3.f);
				m_staticObjects.emplace_back(std::make_unique<Coin>(sprite));
			}
			factor_x += 85.f; 
		}
		factor_y -= 90.f; //the height of each texture
	}
}

// for switch to pasue/menu
void InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{


}

void InGameState::update(sf::Time time)
{
	m_player.move(time);
	std::for_each(m_movingObjects.begin(), m_movingObjects.end(), [&time](auto& entity) {entity->move(time); });
	checkCollision();
}

void InGameState::render(sf::RenderWindow&window)
{
	
	sf::Vector2f viewCenter = window.getView().getCenter();
	int offset = static_cast<int>(viewCenter.x) % static_cast<int>(WIDTH);

	m_background.setPosition(viewCenter.x - offset, HEIGHT / 2);

	window.draw(m_background);

	m_background.setPosition(viewCenter.x - offset + WIDTH, HEIGHT / 2);

	window.draw(m_background);

	drawBoard(window);
	m_ui.showGameInfo(window, m_player);
}

void InGameState::insertMovingObject(std::unique_ptr<MovingObject> object)
{
	m_movingObjects.emplace_back(std::move(object));
}

void InGameState::insertStaticObject(std::unique_ptr<StaticObject> object)
{
	m_staticObjects.emplace_back(std::move(object));
}

void InGameState::drawBoard(sf::RenderWindow& window) const
{
	m_player.draw(window);
	std::for_each(m_movingObjects.cbegin(), m_movingObjects.cend(), [&window](const auto& entity) {entity->draw(window); });
	std::for_each(m_staticObjects.cbegin(), m_staticObjects.cend(), [&window](const auto& object) {object->draw(window); });
}

void InGameState::checkCollision()
{

	for (auto& entity : m_movingObjects)
	{
		if (m_player.isCollide(entity->getObjectSprite()))
		{
			auto func = GameCollisions::instance().CollusionFunc(typeid(m_player), typeid(*entity));
			if (func != nullptr)
			{
				func(m_player, *entity);
			}
		}


	}

	for (auto& object : m_staticObjects)
	{
		if (m_player.isCollide(object->getObjectSprite()))
		{
			auto func = GameCollisions::instance().CollusionFunc(typeid(m_player), typeid(*object));
			if (func != nullptr)
			{
				func(m_player, *object);
			}
		}
	}

	for (auto entity1 = m_movingObjects.begin(); entity1 != m_movingObjects.end(); ++entity1)
	{
		auto entity2 = entity1;
		for (++entity2; entity2!= m_movingObjects.end(); ++entity2)
		{
			if ((*entity1)->isCollide((*entity2)->getObjectSprite()))
			{
				auto func = GameCollisions::instance().CollusionFunc(typeid(**entity1), typeid(**entity2));
				if (func != nullptr)
				{
					func(*(*entity1), *(*entity2));
				}
			}
		}
	}
	for (auto entity = m_movingObjects.begin(); entity != m_movingObjects.end(); ++entity)
	{
		for (auto object = m_staticObjects.begin(); object != m_staticObjects.end(); ++object)
		{
			if ((*entity)->isCollide((*object)->getObjectSprite()))
			{
				auto func = GameCollisions::instance().CollusionFunc(typeid(**entity), typeid(**object));
				if (func != nullptr)
				{
					func(*(*entity), *(*object));
				}
			}
		}
	}
	m_movingObjects.remove_if([](const auto& movingObject) { return movingObject->ToErase(); });
	m_staticObjects.remove_if([](const auto& staticObject) { return staticObject->ToErase();});
}

sf::Sprite InGameState::createNewObjectSprite(float x, float y, const std::string filename,float scale)const
{
	sf::Sprite sprite = sf::Sprite(ResourceManager::instance().getTexture(filename));
	sprite.setPosition(x, y);
	sprite.setScale({ scale,scale });
	return sprite;
}