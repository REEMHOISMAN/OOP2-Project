#include "DesignPatterns/States/GameState/InGameState.h"
#include "DesignPatterns/Singletons/ResourceManager.h"
#include "DesignPatterns/Command/SwitchScreenCommand.h"
#include "CollisionHandling.h"
#include "GameController.h"

/*================== InGameState constructor =================*/
/*---------------------------------------------------------
* this state actually "runs" the game itself
* being entered from the menu.
* can switch from the game to either GameOver
* the game holds the player - its life is one of the conditions
* to leave this state
-----------------------------------------------------------*/
InGameState::InGameState(GameController& controller, GameOverState& gameOver,  Button& button) :
			m_level(*this), m_player(m_level), m_soundButton(button), m_controller(controller), m_isPause(false), m_gameOver(gameOver),m_levelNum(0)
{
	m_background.setTexture(&ResourceManager::instance().getTexture("gameBG"));
	m_background.setSize({float(WIDTH*3), float(HEIGHT*3)});
	m_background.setOrigin(m_background.getSize().x / 2, m_background.getSize().y / 2);

	m_playlist.open("playlist.txt");

	m_pause.setTexture(&ResourceManager::instance().getTexture("pause"));
	
	m_pause.setSize({ 360.f, 360.f });
	m_pause.setOrigin(m_pause.getSize().x / 2, m_pause.getSize().y / 2);
	m_pause.setPosition(m_player.getObjectSprite().getPosition());

	sf::Sprite sprite(ResourceManager::instance().getTexture("playerSpriteSheet"));
	sprite.scale({ 0.35f, 0.35f });
	m_player.setObjectSprite(sprite);
	
	initCollisionFunctions();
	readNewLevel();
}

/*================== InGameState constructor =================*/
/*---------------------------------------------------------
* while the user is already in this state - means he is playing
* the only events that can happen during game run is either 
* soundButton or "ESC" key was press in order to pause the game
-----------------------------------------------------------*/
void InGameState::handleEvent(sf::Event& event, sf::RenderWindow& window)// change to handle event
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2f pos = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		m_soundButton.handleClick(pos);
	}
	else if (event.type == sf::Event::KeyReleased) {
		
		if (event.key.code == sf::Keyboard::Escape) {
			m_isPause = !m_isPause;
		}
	}
}

/*================== update =================*/
void InGameState::update(sf::Time time)
{
	if (m_isPause) return; // no update is needed
	
	if (!m_playlist.is_open()) { // the user wants a new game after finishing the game first time
		m_playlist.open("playlist.txt");
		readNewLevel();
	}
	m_player.move(time);
	m_level.updateLevel(time, m_player);
	
	if (m_player.getHearts() == 0) { //player is dead 
		m_playlist.close();
		m_controller.changeState(m_gameOver);
	}	
}

/*================== render =================*/
void InGameState::render(sf::RenderWindow&window)
{
	setView(window);
	m_level.draw(window);
	if (m_level.isLevelFinished()) return;

	m_player.draw(window);
	
	m_ui.showGameInfo(window, m_player, m_level.levelPizzaAmount());
	m_soundButton.setPosition({ window.getView().getCenter().x + 450.f, window.getView().getCenter().y - 330.f });
	m_soundButton.draw(window);

	if (m_isPause) {
		sf::RectangleShape blurBG;
		blurBG.setFillColor({ 0,0,0,200 });
		blurBG.setSize({WIDTH, HEIGHT});
		blurBG.setOrigin({ WIDTH / 2, HEIGHT / 2 });
		blurBG.setPosition(window.getView().getCenter());
		window.draw(blurBG);
		m_pause.setPosition(window.getView().getCenter());
		window.draw(m_pause);
	}
}

/*================== setView =================*/
void InGameState::setView(sf::RenderWindow& window)
{
	sf::Vector2f viewCenter = window.getView().getCenter();
	int offset = static_cast<int>(viewCenter.x) % static_cast<int>(WIDTH*3);

	m_background.setPosition(static_cast<float>(viewCenter.x - offset), static_cast<float>(HEIGHT/5));
	window.draw(m_background);

	m_background.setPosition(static_cast<float>(viewCenter.x - offset + 3*WIDTH), static_cast<float>(HEIGHT/5));
	window.draw(m_background);
}

/*================== readNewLevel =================*/
void InGameState::readNewLevel()
{
	m_player.resetPizzaAmount();
	m_player.resetGravity();
	auto levelName = std::string();
	if (std::getline(m_playlist, levelName)) {
		m_levelNum++;
		if (levelName != "level" + std::to_string(m_levelNum) + ".png") { // the only valid format to the level png (see README)
			throw std::runtime_error("level format isn't valid!");
		}
		m_level.readLevelMap(levelName, m_player); // load level board from png
	}
	else {
		m_playlist.close();
		m_controller.changeState(m_gameOver); // no more level to read (eof) game over
	}
}

/*================== endGame =================*/
void InGameState::endGame(sf::RenderWindow& window)
{
	std::string outputMessege = m_player.getHearts() == 0 ? "Better Luck Next Time!!" : "levels complete succefully!!";
	m_ui.showFinelScore(window, outputMessege, m_player.getCoins(), m_levelNum);
}

/*================== resetGame =================*/
void InGameState::resetGame()
{
	m_levelNum = 0;
	m_player.resetPlayer();
	m_level.resetLevel();
}