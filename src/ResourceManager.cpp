#include "ResourceManager.h"
#include <iostream>
#include "States/PlayerState/WalkState.h"
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
}

/*================== getTexture =================*/
sf::Texture& ResourceManager::getTexture(const std::string type)
{
    return m_textures[type];
}

/*================== initTextures =================*/
void ResourceManager::initTextures()
{
    std::array<std::string, NUM_OF_TEXTURES> textureNames =
    { "playerSpriteSheet", "background", "tileMap", "mainGround", "ground", "basicEnemiesSheet","PizzaEnemySheet"};

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