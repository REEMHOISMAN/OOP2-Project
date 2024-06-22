#include "DesignPatterns/Singletons/ResourceManager.h"
#include <iostream>
#include "DesignPatterns/States/PlayerState/WalkState.h"
#include <array>

/*================== instance =================*/
/**----------------------------------------------
 * this class is a 'singletone' class -> this function is the way
   other classes can reach to this class 'getters'
 *---------------------------------------------**/
ResourceManager& ResourceManager::instance()
{
    static ResourceManager instance;
    return instance;
}

/*================== ResourcesManager constructor =================*/
ResourceManager::ResourceManager()
{
    initTextures();
    initAnimations();
}


/*================== getTexture =================*/
sf::Texture& ResourceManager::getTexture(const std::string type)
{
    return m_textures[type];
}

/*================== initAnimations =================*/
/**----------------------------------------------
 * each enemy (or player state) had is own vector of animation
 *---------------------------------------------**/
void ResourceManager::initAnimations()
{
    m_animations.emplace(std::make_pair(PLAYER_STAND, std::vector<sf::IntRect>{sf::IntRect({ 188, 50, 170, 390 })}));
    
    m_animations.emplace(std::make_pair(PLAYER_WALK, std::vector<sf::IntRect>{sf::IntRect({ 188, 50 , 170, 390 }),
                                                                              sf::IntRect(639, 50, 190, 411) }));
    
    m_animations.emplace(std::make_pair(PLAYER_RUN, std::vector<sf::IntRect>{sf::IntRect(1142, 26, 187, 390),
                                                                             sf::IntRect(1619, 42, 197, 390),
                                                                             sf::IntRect(204, 527, 184, 390) }));
   
    m_animations.emplace(std::make_pair(PLAYER_JUMP, std::vector<sf::IntRect>{sf::IntRect(639, 50, 190, 411) }));

    m_animations.emplace(std::make_pair(PLAYER_DIVE, std::vector<sf::IntRect>{sf::IntRect(1472, 1040, 488, 430)}));

    m_animations.emplace(std::make_pair(PLAYER_CHEESED, std::vector<sf::IntRect>{sf::IntRect(167, 1588, 253, 391),
                                                                                 sf::IntRect(673, 1580, 253, 390),
                                                                                 sf::IntRect(1147, 1580, 253, 400)}));

    m_animations.emplace(std::make_pair(ONION_ENEMY, std::vector<sf::IntRect>{ sf::IntRect({ 45,50, 54,62 }),
                                                                               sf::IntRect({ 115,50, 54,62 }),
                                                                               sf::IntRect({ 188,50, 54,62 }) }));

    m_animations.emplace(std::make_pair(PEPPER_ENEMY, std::vector<sf::IntRect>{ sf::IntRect({ 55,198, 40,54 }),
                                                                                sf::IntRect({ 125,197, 40,54 }),
                                                                                sf::IntRect({ 193,197, 40,54 }) }));
    
    m_animations.emplace(std::make_pair(ORANGE_ENEMY, std::vector<sf::IntRect>{ sf::IntRect({ 134,140,37,34 }),
                                                                                sf::IntRect({ 198,140,37,33 }) }));

    m_animations.emplace(std::make_pair(PIZZA_ENEMY_MOVE, std::vector<sf::IntRect>{ sf::IntRect({ 87,90,175,148 }),
                                                                                    sf::IntRect({ 304,88,171,148 }),
                                                                                    sf::IntRect({ 517,88,171,148 })}));
    
    m_animations.emplace(std::make_pair(PIZZA_ENEMY_ATTACK, std::vector<sf::IntRect>{  sf::IntRect({ 517,88,171,148 }),
                                                                                       sf::IntRect({ 738,88,174,148 }),
                                                                                       sf::IntRect({ 67,319,196,151 })}));

 }
/*================== getAnimation =================*/
std::vector<sf::IntRect>& ResourceManager::getAnimation(const ObjectAnimation type)
{
    auto it = m_animations.find(type);
    if (it != m_animations.end())
    {
        return it->second; //returns the relevant animation vector ->depend on the type of state/enemy
    }
    else {
        throw std::runtime_error("type not found in the map");
    }
}

/*================== initTextures =================*/
void ResourceManager::initTextures()
{
    std::array<std::string, NUM_OF_TEXTURES> textureNames =
    { "playerSpriteSheet", "background", "frameBackground",  "tileMap", "mainGround", "ground", "basicEnemiesSheet","PizzaEnemySheet", "cheese","salt"};

    for (int i = 0; i < NUM_OF_TEXTURES; ++i)
    {
        sf::Texture texture;

        if (!texture.loadFromFile(textureNames[i] + ".png")) failedLoad(textureNames[i] + ".png");

        m_textures[textureNames[i]] = texture;
        m_textures[textureNames[i]].setSmooth(true);
    }
}

/*================== failedLoad =================*/
void ResourceManager::failedLoad(const std::string msg) const
{
    std::cerr << "failed load " << msg << " in ResourceManager\n";
    exit(1);
}