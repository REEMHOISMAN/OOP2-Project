#include "States/GameState/InGameState.h"
#include "ResourceManager.h"
#include "GameCollisions.h"
#include "CollisionHandling.h"
#include "Factories/EnemyFactory.h"
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
				m_objects.emplace_back(std::make_unique<Obstacle>(sprite));
			}
			else if (color == sf::Color::Black)
			{
				sprite = createNewObjectSprite(factor_x, factor_y, "ground");
				m_objects.emplace_back(std::make_unique<Obstacle>(sprite));
			}
			else if (image.getPixel(x, y) == sf::Color::Red)
			{
				sprite = createNewObjectSprite(factor_x, 300, "playerSpriteSheet");
				sprite.setTextureRect(sf::IntRect(sf::Vector2i(174, 50), sf::Vector2i(170, 390)));
				sprite.scale(0.4f, 0.4f);
				sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
				m_entities.emplace_back(std::make_unique<Player>(sprite));
			}
			else if (image.getPixel(x, y) == sf::Color(115, 43, 245))
			{
				sprite = createNewObjectSprite(factor_x,300, "basicEnemiesSheet");
				m_entities.emplace_back(EnemyFactory::createSideToSideEnemy(ONION_ENEMY, sprite, 1.9f));
			}
			else if (image.getPixel(x, y) == sf::Color(55, 126, 71))
			{
				sprite = createNewObjectSprite(factor_x, 300, "basicEnemiesSheet");
				m_entities.emplace_back(EnemyFactory::createSideToSideEnemy(PEPPER_ENEMY, sprite,1.9f));
			}
			else if (image.getPixel(x, y) == sf::Color(255, 127, 39))
			{
				sprite = createNewObjectSprite(factor_x, 600, "basicEnemiesSheet");
				m_entities.emplace_back(EnemyFactory::createJumpingEnemy(ORANGE_ENEMY, sprite));
			}
			else if (image.getPixel(x, y) == sf::Color(255, 201, 14))
			{
				sprite = createNewObjectSprite(factor_x, 600, "PizzaEnemySheet");
				m_entities.emplace_back(EnemyFactory::createSideToSideEnemy(PIZZA_ENEMY, sprite,0.85f));
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
				auto func = GameCollisions::instance().CollusionFunc(typeid(**entity), typeid(**object));
				if (func)
				{
					func(*(*entity).get(), *(*object).get());
				}
			}
		}
	}
}

sf::Sprite InGameState::createNewObjectSprite(float x, float y, const std::string filename)const
{
	sf::Sprite sprite = sf::Sprite(ResourceManager::instance().getTexture(filename));
	sprite.setPosition(x, y);
	return sprite;
}