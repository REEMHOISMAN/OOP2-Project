#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "CollisionHandling.h"
#include "DesignPatterns/Factories/EnemyFactory.h"
#include "GameObject/StaticObject/StaticSaltBomb.h"
#include "Macros.h"

InGameState::InGameState()
{
	auto texture = &ResourceManager::instance().getTexture("background");
	m_background.setTexture(texture);
	m_background.setSize({float(WIDTH), float(HEIGHT)});
	m_background.setOrigin(m_background.getSize().x / 2, m_background.getSize().y / 2);
	m_background.setPosition(WIDTH/2, HEIGHT/2);
	

	m_userInterfaceFrame.setTexture(&ResourceManager::instance().getTexture("frameBackground"));
	m_userInterfaceFrame.setSize({ float(WIDTH), float(HEIGHT) });
	m_userInterfaceFrame.setOrigin(m_userInterfaceFrame.getSize().x / 2, m_userInterfaceFrame.getSize().y / 2);
	m_userInterfaceFrame.setPosition(WIDTH / 2, HEIGHT/2);
	initTileMap();
	initCollisionFunctions();
}


void InGameState::initTileMap()
{
	auto image = sf::Image();
	float factor_y = 620.f; 
	image.loadFromFile("tileMap.png");
	sf::Sprite sprite;
	
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
				m_movingObjects.emplace_back(std::make_unique<Player>(sprite));
			}
			else if (image.getPixel(x, y) == sf::Color(115, 43, 245))
			{
				sprite = createNewObjectSprite(factor_x,300, "basicEnemiesSheet");
				m_movingObjects.emplace_back(EnemyFactory::createEnemy(ONION_ENEMY, sprite, 1.9f, *this));
			}
			else if (image.getPixel(x, y) == sf::Color(55, 126, 71))
			{
				sprite = createNewObjectSprite(factor_x, 300, "basicEnemiesSheet");
				m_movingObjects.emplace_back(EnemyFactory::createEnemy(PEPPER_ENEMY, sprite,1.9f, *this));
			}
			else if (image.getPixel(x, y) == sf::Color(255, 127, 39))
			{
				sprite = createNewObjectSprite(factor_x, 300, "basicEnemiesSheet");
				m_movingObjects.emplace_back(EnemyFactory::createEnemy(ORANGE_ENEMY, sprite, 1.9f, *this));
			}
			else if (image.getPixel(x, y) == sf::Color(255, 201, 14))
			{
				sprite = createNewObjectSprite(factor_x,500, "PizzaEnemySheet");
				m_movingObjects.emplace_back(EnemyFactory::createEnemy(PIZZA_ENEMY_MOVE, sprite,0.85f, *this));
			}
			else if (image.getPixel(x, y) == sf::Color(195, 195, 195))
			{
				sprite = createNewObjectSprite(factor_x, MIN_Y, "salt",2.f);
				m_staticObjects.emplace_back(std::make_unique<StaticSaltBomb>(sprite));
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
	std::for_each(m_movingObjects.begin(), m_movingObjects.end(), [&time](auto& entity) {entity->move(time); });
	checkCollision();
}

void InGameState::render(sf::RenderWindow&window)
{
	
	sf::Vector2f viewCenter = window.getView().getCenter();
	float viewWidth = window.getView().getSize().x;
	float offset = static_cast<int>(viewCenter.x) % static_cast<int>(WIDTH);

	m_background.setPosition(viewCenter.x - offset, HEIGHT / 2);

	window.draw(m_background);

	m_background.setPosition(viewCenter.x - offset + WIDTH, HEIGHT / 2);

	window.draw(m_background);

	drawBoard(window);
	m_userInterfaceFrame.setPosition(window.getView().getCenter());
	window.draw(m_userInterfaceFrame);
}

void InGameState::drawBoard(sf::RenderWindow& window) const
{
	std::for_each(m_movingObjects.cbegin(), m_movingObjects.cend(), [&window](const auto& entity) {entity->draw(window); });
	std::for_each(m_staticObjects.cbegin(), m_staticObjects.cend(), [&window](const auto& object) {object->draw(window); });
}

void InGameState::checkCollision()
{

	for (auto entity1 = m_movingObjects.begin(); entity1 != m_movingObjects.end(); ++entity1)
	{
		for (auto entity2 = entity1+1; entity2!= m_movingObjects.end(); ++entity2)
		{
		
		}
	}

	for (auto entity = m_movingObjects.begin(); entity != m_movingObjects.end(); ++entity)
	{
		for (auto object = m_staticObjects.begin(); object != m_staticObjects.end(); ++object)
		{
			if ((*entity)->isCollide((*object)->getObjectSprite()))
			{
				auto func = GameCollisions::instance().CollusionFunc(typeid(**entity), typeid(**object));
				if (func)
				{
					func(*(*entity).get(), *(*object).get());
				}
			}
		}
	}
	std::erase_if(m_staticObjects, [](const auto& staticObject) { return staticObject->ToErase();});
}

sf::Sprite InGameState::createNewObjectSprite(float x, float y, const std::string filename,float scale)const
{
	sf::Sprite sprite = sf::Sprite(ResourceManager::instance().getTexture(filename));
	sprite.setPosition(x, y);
	sprite.setScale({ scale,scale });
	return sprite;
}