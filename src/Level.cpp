#include "Level.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Singletons/GameCollisions.h"
#include "CollisionHandling.h"
#include "DesignPatterns/Factories/MovingObjectFactory.h"
#include "DesignPatterns/Factories/StaticObjectFactory.h"
#include "GameObject/MovingObject/MovingObject.h"
#include "GameObject/StaticObject/StaticObject.h"
#include "GameController.h"
#include "GameObject/MovingObject/Cage.h"

//-----------------------------------------------------------------------------
Level::Level(InGameState& game) :m_game(game), m_pizzas(0), m_levelFinishTimer(sf::seconds(1.5f)), m_levelFinish(false)
{
	m_loadLevel.setTexture(&ResourceManager::instance().getTexture("loading"));
	m_loadLevel.setSize({ static_cast<float>(WIDTH/2), static_cast<float>(HEIGHT/2) });
	m_loadLevel.setOrigin(m_loadLevel.getGlobalBounds().width / 2, m_loadLevel.getGlobalBounds().height / 2);
}


//-----------------------------------------------------------------------------
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
			if (color == sf::Color::Red)
			{
				player.setPlayer(factor_x, 300);
			}
			else if (auto movingObject = MovingObjectFactory::createMovingObject(color, factor_x, factor_y, this))
			{
				m_movingObjects.emplace_back(std::move(movingObject));
			}
			else if (auto staticObject = StaticObjectFactory::createStaticObject(color, factor_x, factor_y))
			{
				m_staticObjects.emplace_back(std::move(staticObject));
			}
			else if (color == sf::Color(127, 127, 127))
			{
				m_movingObjects.emplace_back(std::make_unique<Cage>(factor_x, factor_y - 205));
				auto* cagePtr = dynamic_cast<Cage*>(m_movingObjects.back().get());
				player.setCage(cagePtr);
			}
			factor_x += 85.f;
		}
		factor_y -= 90.f; 
	}

}

//-----------------------------------------------------------------------------
void Level::updateLevel(sf::Time& time, Player& player)
{
	if (!m_levelFinish) { //level is NOT finish!
		
		std::for_each(m_movingObjects.begin(), m_movingObjects.end(), [&time](auto& movingObject) {movingObject->move(time); }); //move object..
		
		proccessCollusionWithPlayer(player, m_movingObjects.begin(), m_movingObjects.end()); // player and moving objects collusion
		proccessCollusionWithPlayer(player, m_staticObjects.begin(), m_staticObjects.end()); // player and static objects collusion
		processCollisions(m_movingObjects.begin(), m_movingObjects.end(), std::next(m_movingObjects.begin()), m_movingObjects.end()); //moving with moving collusion
		processCollisions(m_movingObjects.begin(), m_movingObjects.end(), m_staticObjects.begin(), m_staticObjects.end());  //moving with static collusion

		m_movingObjects.remove_if([](const auto& movingObject) { return movingObject->ToErase(); });
		m_staticObjects.remove_if([](const auto& staticObject) { return staticObject->ToErase(); });
	}
	
	if (m_levelFinish && m_levelFinishTimer.asSeconds() > 0.f) { //level is finish but still "loading.." new level
		m_levelFinishTimer -= time;
	}

	else if (m_levelFinish) { //level is finish and also the loading is finished!
		resetLevel();
	}
}


//-----------------------------------------------------------------------------
template<typename T>
void Level::proccessCollusionWithPlayer(Player& player, T begin, T end)
{
	for (auto it = begin; it != end; ++it)
	{
		if (player.isCollide((*it)->getObjectSprite())) {
			auto func = GameCollisions::instance().CollusionFunc(typeid(player), typeid(**it));
			if (func) {
				func(player, **it);
			}
		}
	}
}

//-----------------------------------------------------------------------------
template<typename T1, typename T2>
void Level::processCollisions(T1 begin1, T1 end1, T2 begin2, T2 end2)
{
	for (auto it1 = begin1; it1 != end1; ++it1)
	{
		for (auto it2 = begin2; it2 != end2; ++it2)
		{
			if ((*it1)->isCollide((*it2)->getObjectSprite())) {
				auto func = GameCollisions::instance().CollusionFunc(typeid(**it1), typeid(**it2));
				if (func) {
					func(**it1, **it2);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
void Level::insertMovingObject(std::unique_ptr<MovingObject> object)
{
	m_movingObjects.emplace_back(std::move(object));
}

//-----------------------------------------------------------------------------
void Level::insertStaticObject(std::unique_ptr<StaticObject> object)
{
	m_staticObjects.emplace_back(std::move(object));
}

//-----------------------------------------------------------------------------
void Level::draw(sf::RenderWindow& window)
{
	if (m_levelFinish){
		m_loadLevel.setPosition(window.getView().getCenter());
		window.clear();
		window.draw(m_loadLevel);
		return;
	}
	std::for_each(m_movingObjects.crbegin(), m_movingObjects.crend(), [&window](const auto& moving) {moving->draw(window); });
	std::for_each(m_staticObjects.cbegin(), m_staticObjects.cend(), [&window](const auto& stati) {stati->draw(window); });
}

//-----------------------------------------------------------------------------
void Level::setLevelFinished()
{
	m_levelFinish = true;
}

//-----------------------------------------------------------------------------
// the player saved his friend. new level is about to be loading -> reset everything
void Level::resetLevel()
{
	m_movingObjects.clear();
	m_staticObjects.clear();
	m_pizzas = 0;
	m_levelFinish = false;
	m_levelFinishTimer = sf::seconds(1.5f);
	m_game.readNewLevel();
}

//-----------------------------------------------------------------------------
void Level::inceasePizzaAmount()
{
	++m_pizzas;
}

//-----------------------------------------------------------------------------
int Level::levelPizzaAmount() const
{
	return m_pizzas;
}

//-----------------------------------------------------------------------------
bool Level::isLevelFinished() const
{
	return m_levelFinish;
}
