#include "Level.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "CollisionHandling.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"
#include "GameObject/MovingObject/MovingObject.h"
#include "GameObject/StaticObject/StaticObject.h"
#include "GameController.h"

Level::Level(InGameState& game)
	:m_game(game)
{

}

void Level::readLevelMap(const std::string levelImgName, Player& player)
{
	auto image = sf::Image();
	image.loadFromFile(levelImgName);

	sf::Sprite sprite;
	float factor_y = 620.f;
	for (int y = int(image.getSize().y) - 1; y >= 0; y--) // read from the end because print from the begin
	{
		float factor_x = 0.f;
		for (int x = 0; x < int(image.getSize().x); x++)
		{
			auto color = image.getPixel(x, y);
			if (image.getPixel(x, y) == sf::Color::Red)
			{
				player.setPlayer(factor_x, 300);
			}
			else if (auto movingObject = MovingObjectFactory::createMovingObject(color, factor_x, 300, this))
			{
				m_movingObjects.emplace_back(std::move(movingObject));
			}
			else if (auto staticObject = StaticObjectFactory::createStaticObject(color, factor_x, factor_y))
			{
				m_staticObjects.emplace_back(std::move(staticObject));
			}
			factor_x += 85.f;
		}
		factor_y -= 90.f; //the height of each texture
	}

}

void Level::updateLevel(sf::Time& time, Player& player)
{
	std::for_each(m_movingObjects.begin(), m_movingObjects.end(), [&time](auto& movingObject) {movingObject->move(time); });
	checkCollision(player);
}

void Level::checkCollision(Player& player)
{
	for (auto& entity : m_movingObjects)
	{
		if (player.isCollide(entity->getObjectSprite()))
		{
			auto func = GameCollisions::instance().CollusionFunc(typeid(player), typeid(*entity));
			if (func != nullptr)
			{
				func(player, *entity);
			}
		}
	}

	for (auto& object : m_staticObjects)
	{
		if (player.isCollide(object->getObjectSprite()))
		{
			auto func = GameCollisions::instance().CollusionFunc(typeid(player), typeid(*object));
			if (func != nullptr)
			{
				func(player, *object);
			}
		}
	}

	for (auto entity1 = m_movingObjects.begin(); entity1 != m_movingObjects.end(); ++entity1)
	{
		auto entity2 = entity1;
		for (++entity2; entity2 != m_movingObjects.end(); ++entity2)
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

void Level::insertMovingObject(std::unique_ptr<MovingObject> object)
{
	m_movingObjects.emplace_back(std::move(object));
}

void Level::insertStaticObject(std::unique_ptr<StaticObject> object)
{
	m_staticObjects.emplace_back(std::move(object));
}


void Level::draw(sf::RenderWindow& window) const
{
	std::for_each(m_movingObjects.cbegin(), m_movingObjects.cend(), [&window](const auto& moving) {moving->draw(window); });
	std::for_each(m_staticObjects.cbegin(), m_staticObjects.cend(), [&window](const auto& stati) {stati->draw(window); });
}
