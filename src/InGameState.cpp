#include "InGameState.h"
#include "ResourceManager.h"
#include "Macros.h"

InGameState::InGameState()
{
	m_background.setTexture(&ResourceManager::instance().getTexture("background"));
	m_background.setSize({float(WIDTH), float(HEIGHT)});
	initTileMap();
}


void InGameState::initTileMap()
{
	auto image = sf::Image();
	int i = 0;
	float factor_y = 710.f; 

	image.loadFromFile("tileMap.png");
	m_tileMap.resize(image.getSize().y); // as the number of rows in the image

	for (int y = int(image.getSize().y)-1; y >= 0; y--) // read from the end because print from the begin
	{
		float factor_x = 0.f;
		for (int x = 0; x < int(image.getSize().x); x++)
		{
			if (image.getPixel(x, y) == sf::Color::Green) //if the current pixel is green than the sprite will be with grass
			{
				m_tileMap[i].push_back(sf::Sprite(ResourceManager::instance().getTexture("mainGround")));
				m_tileMap[i].back().setPosition(factor_x, factor_y);
				m_tileMap[i].back().setScale(0.2, 0.2);
			}
			else if (image.getPixel(x, y) == sf::Color::Black) //if the current pixel is red than the sprite will be without grass
			{
				m_tileMap[i].push_back(sf::Sprite(ResourceManager::instance().getTexture("ground")));
				m_tileMap[i].back().setPosition(factor_x, factor_y);
				m_tileMap[i].back().setScale(0.2, 0.2);
			}
			factor_x += 17.f; //the width of each texture
		}
		factor_y -= 18.f; //the height of each texture
		i++; 
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

void InGameState::update(sf::Time dt)
{
}

void InGameState::render(sf::RenderWindow&window)
{
	window.setView(window.getDefaultView());
	window.draw(m_background);
	drawBoard(window);
	m_player.draw(window);
}

void InGameState::drawBoard(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_tileMap.size(); i++)
	{
		for (int j = 0; j < m_tileMap[i].size(); j++)
		{
			window.draw(m_tileMap[i][j]);
		}
	}
}
