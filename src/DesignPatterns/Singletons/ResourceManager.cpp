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
ResourceManager::ResourceManager() : m_muteSound(false)
{
    initTextures();
    initAnimations();
    initSounds();
    m_font.loadFromFile("papaLoueiFont.ttf");
    m_font.setSmooth(true);
}


/*================== getTexture =================*/
sf::Texture& ResourceManager::getTexture(const std::string type)
{
    return m_textures[type];
}


sf::Font& ResourceManager::getFont()
{
    return m_font;
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
    
    m_animations.emplace(std::make_pair(PLAYER_STAND_PIZZA, std::vector<sf::IntRect>{sf::IntRect({ 611, 567, 228, 388 })}));
    
    m_animations.emplace(std::make_pair(PLAYER_WALK_PIZZA, std::vector<sf::IntRect>{sf::IntRect({ 611, 567, 228, 388 }),
                                                                                    sf::IntRect(1058, 561, 264, 410) }));
    
    m_animations.emplace(std::make_pair(PLAYER_RUN_PIZZA, std::vector<sf::IntRect>{sf::IntRect(1545, 548, 265, 409),
                                                                             sf::IntRect(98, 1077, 273, 401),
                                                                             sf::IntRect(625, 1082, 239, 388) }));
   
    m_animations.emplace(std::make_pair(PLAYER_JUMP_PIZZA, std::vector<sf::IntRect>{sf::IntRect(1058, 561, 264, 410) }));


    m_animations.emplace(std::make_pair(FAT_MAN_HAPPY, std::vector<sf::IntRect>{sf::IntRect(639, 390, 365, 284) }));

    m_animations.emplace(std::make_pair(FAT_MAN_ANGRY, std::vector<sf::IntRect>{sf::IntRect(299, 396, 325, 279)}));

    m_animations.emplace(std::make_pair(FAT_MAN_MOVE, std::vector<sf::IntRect>{sf::IntRect(0, 91, 350, 207),
                                                                               sf::IntRect(360, 89, 350, 224),
                                                                               sf::IntRect(709, 83, 350, 224)}));//307

    m_animations.emplace(std::make_pair(PLAYER_CROUCH, std::vector<sf::IntRect>{sf::IntRect(1142, 1088, 228, 392)}));

    m_animations.emplace(std::make_pair(ONION_ENEMY, std::vector<sf::IntRect>{ sf::IntRect({ 45,50, 54,62 }),
                                                                               sf::IntRect({ 115,50, 54,62 }),
                                                                               sf::IntRect({ 188,50, 54,62 }) }));

    m_animations.emplace(std::make_pair(PEPPER_ENEMY, std::vector<sf::IntRect>{ sf::IntRect({ 55,198, 40,54 }),
                                                                                sf::IntRect({ 125,197, 40,54 }),
                                                                                sf::IntRect({ 193,197, 40,54 }) }));
    
    m_animations.emplace(std::make_pair(ORANGE_ENEMY, std::vector<sf::IntRect>{ sf::IntRect({ 134,140,37,34 }),
                                                                                sf::IntRect({ 198,140,37,33 }) }));

    m_animations.emplace(std::make_pair(PIZZA_ENEMY_MOVE, std::vector<sf::IntRect>{ sf::IntRect({ 87,90,175,148 }),
                                                                                    sf::IntRect({ 304,89,171,148 }),
                                                                                    sf::IntRect({ 517,88,171,148 })}));
    
    m_animations.emplace(std::make_pair(PIZZA_ENEMY_ATTACK, std::vector<sf::IntRect>{  sf::IntRect({ 517,88,171,148 }),
                                                                                       sf::IntRect({ 738,88,174,148 }),
                                                                                       sf::IntRect({ 67,319,196,151 })}));

    m_animations.emplace(std::make_pair(PIZZA_ENEMY_DIE, std::vector<sf::IntRect>{  sf::IntRect({ 311,322,171,148 }),
                                                                                    sf::IntRect({ 543,328,152,140 }),
                                                                                    sf::IntRect({ 530,578,155,92 }),
                                                                                    sf::IntRect({ 743,596,151,75 }), 
                                                                                    sf::IntRect({ 753,333,102,143 })}));

    m_animations.emplace(std::make_pair(EXPLOSION, std::vector<sf::IntRect>{  sf::IntRect({ 34,115,116,61 }),
                                                                              sf::IntRect({ 257,127,105,53 }),
                                                                              sf::IntRect({ 498,101,118,86 }),
                                                                              sf::IntRect({ 750,71,156,126 }),
                                                                              sf::IntRect({ 1015,57,187,138 })}));

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
    { "playerSpriteSheet", "background", "frameBackground", "menuBackground",
       "mainGround", "ground", "basicEnemiesSheet","PizzaEnemySheet",  "buttons", "controls", "cage", "friend", "loading",
        "cheese","salt", "explosionSpriteSheet","heart","coin", "papaLoueiHead","pizza","fatPerson","ladder" };

    for (int i = 0; i < NUM_OF_TEXTURES; ++i)
    {
        sf::Texture texture;

        if (!texture.loadFromFile(textureNames[i] + ".png")) failedLoad(textureNames[i] + ".png");

        m_textures[textureNames[i]] = texture;
        m_textures[textureNames[i]].setSmooth(true);
    }
}
/*================== initSounds =================*/
void ResourceManager::initSounds()
{
    std::array<std::string, NUM_OF_SOUNDS>soundsName = 
    { "coinSound","explodeSound","flySound","jumpSound","levelUpSound"
        ,"playerEnemySound","takeSaltSound" };
    for (int i = 0; i < NUM_OF_SOUNDS; ++i)
    {
        sf::SoundBuffer sound;
        if (!sound.loadFromFile(soundsName[i] + ".ogg")) failedLoad(soundsName[i] + ".ogg");

        m_sounds[soundsName[i]] = sound;
    }
}

/*================== failedLoad =================*/
void ResourceManager::failedLoad(const std::string msg) const
{
    std::cerr << "failed load " << msg << " in ResourceManager\n";
    exit(1);
}
void ResourceManager::playSound(const std::string& soundName,bool val)
{
    if (m_muteSound) return;

    if (val)
    {
        m_currentSound.setVolume(99.9f);
    }
    if (m_currentSound.getStatus() != sf::Sound::Playing) {
        m_currentSound.setBuffer(m_sounds[soundName]);
        m_currentSound.play();
    }
    
 
}

void ResourceManager::setSoundStatus()
{
    m_muteSound = !m_muteSound;
}
